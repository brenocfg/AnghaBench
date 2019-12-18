#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct of_irq {int size; struct device_node* controller; int /*<<< orphan*/  specifier; } ;
struct device_node {char* full_name; } ;
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 int EINVAL ; 
 int OF_IMAP_NO_PHANDLE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 struct device_node* of_irq_dflt_pic ; 
 struct device_node* of_irq_find_parent (struct device_node*) ; 
 int of_irq_workarounds ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

int of_irq_map_raw(struct device_node *parent, const u32 *intspec, u32 ointsize,
		const u32 *addr, struct of_irq *out_irq)
{
	struct device_node *ipar, *tnode, *old = NULL, *newpar = NULL;
	const u32 *tmp, *imap, *imask;
	u32 intsize = 1, addrsize, newintsize = 0, newaddrsize = 0;
	int imaplen, match, i;

	pr_debug("of_irq_map_raw: par=%s,intspec=[0x%08x 0x%08x...],"
		"ointsize=%d\n",
		parent->full_name, intspec[0], intspec[1], ointsize);

	ipar = of_node_get(parent);

	/* First get the #interrupt-cells property of the current cursor
	 * that tells us how to interpret the passed-in intspec. If there
	 * is none, we are nice and just walk up the tree
	 */
	do {
		tmp = of_get_property(ipar, "#interrupt-cells", NULL);
		if (tmp != NULL) {
			intsize = *tmp;
			break;
		}
		tnode = ipar;
		ipar = of_irq_find_parent(ipar);
		of_node_put(tnode);
	} while (ipar);
	if (ipar == NULL) {
		pr_debug(" -> no parent found !\n");
		goto fail;
	}

	pr_debug("of_irq_map_raw: ipar=%s, size=%d\n",
			ipar->full_name, intsize);

	if (ointsize != intsize)
		return -EINVAL;

	/* Look for this #address-cells. We have to implement the old linux
	 * trick of looking for the parent here as some device-trees rely on it
	 */
	old = of_node_get(ipar);
	do {
		tmp = of_get_property(old, "#address-cells", NULL);
		tnode = of_get_parent(old);
		of_node_put(old);
		old = tnode;
	} while (old && tmp == NULL);
	of_node_put(old);
	old = NULL;
	addrsize = (tmp == NULL) ? 2 : *tmp;

	pr_debug(" -> addrsize=%d\n", addrsize);

	/* Now start the actual "proper" walk of the interrupt tree */
	while (ipar != NULL) {
		/* Now check if cursor is an interrupt-controller and if it is
		 * then we are done
		 */
		if (of_get_property(ipar, "interrupt-controller", NULL) !=
				NULL) {
			pr_debug(" -> got it !\n");
			memcpy(out_irq->specifier, intspec,
				intsize * sizeof(u32));
			out_irq->size = intsize;
			out_irq->controller = ipar;
			of_node_put(old);
			return 0;
		}

		/* Now look for an interrupt-map */
		imap = of_get_property(ipar, "interrupt-map", &imaplen);
		/* No interrupt map, check for an interrupt parent */
		if (imap == NULL) {
			pr_debug(" -> no map, getting parent\n");
			newpar = of_irq_find_parent(ipar);
			goto skiplevel;
		}
		imaplen /= sizeof(u32);

		/* Look for a mask */
		imask = of_get_property(ipar, "interrupt-map-mask", NULL);

		/* If we were passed no "reg" property and we attempt to parse
		 * an interrupt-map, then #address-cells must be 0.
		 * Fail if it's not.
		 */
		if (addr == NULL && addrsize != 0) {
			pr_debug(" -> no reg passed in when needed !\n");
			goto fail;
		}

		/* Parse interrupt-map */
		match = 0;
		while (imaplen > (addrsize + intsize + 1) && !match) {
			/* Compare specifiers */
			match = 1;
			for (i = 0; i < addrsize && match; ++i) {
				u32 mask = imask ? imask[i] : 0xffffffffu;
				match = ((addr[i] ^ imap[i]) & mask) == 0;
			}
			for (; i < (addrsize + intsize) && match; ++i) {
				u32 mask = imask ? imask[i] : 0xffffffffu;
				match =
					((intspec[i-addrsize] ^ imap[i])
						& mask) == 0;
			}
			imap += addrsize + intsize;
			imaplen -= addrsize + intsize;

			pr_debug(" -> match=%d (imaplen=%d)\n", match, imaplen);

			/* Get the interrupt parent */
			if (of_irq_workarounds & OF_IMAP_NO_PHANDLE)
				newpar = of_node_get(of_irq_dflt_pic);
			else
				newpar =
					of_find_node_by_phandle((phandle)*imap);
			imap++;
			--imaplen;

			/* Check if not found */
			if (newpar == NULL) {
				pr_debug(" -> imap parent not found !\n");
				goto fail;
			}

			/* Get #interrupt-cells and #address-cells of new
			 * parent
			 */
			tmp = of_get_property(newpar, "#interrupt-cells", NULL);
			if (tmp == NULL) {
				pr_debug(" -> parent lacks "
						"#interrupt-cells!\n");
				goto fail;
			}
			newintsize = *tmp;
			tmp = of_get_property(newpar, "#address-cells", NULL);
			newaddrsize = (tmp == NULL) ? 0 : *tmp;

			pr_debug(" -> newintsize=%d, newaddrsize=%d\n",
				newintsize, newaddrsize);

			/* Check for malformed properties */
			if (imaplen < (newaddrsize + newintsize))
				goto fail;

			imap += newaddrsize + newintsize;
			imaplen -= newaddrsize + newintsize;

			pr_debug(" -> imaplen=%d\n", imaplen);
		}
		if (!match)
			goto fail;

		of_node_put(old);
		old = of_node_get(newpar);
		addrsize = newaddrsize;
		intsize = newintsize;
		intspec = imap - intsize;
		addr = intspec - addrsize;

skiplevel:
		/* Iterate again with new parent */
		pr_debug(" -> new parent: %s\n",
				newpar ? newpar->full_name : "<>");
		of_node_put(ipar);
		ipar = newpar;
		newpar = NULL;
	}
fail:
	of_node_put(ipar);
	of_node_put(old);
	of_node_put(newpar);

	return -EINVAL;
}