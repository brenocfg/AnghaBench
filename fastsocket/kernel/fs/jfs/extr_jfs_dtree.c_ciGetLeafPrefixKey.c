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
typedef  scalar_t__ wchar_t ;
struct component_name {size_t namlen; scalar_t__* name; } ;
typedef  int /*<<< orphan*/  dtpage_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JFS_NAME_MAX ; 
 int JFS_OS2 ; 
 int /*<<< orphan*/  ciToUpper (struct component_name*) ; 
 int /*<<< orphan*/  dtGetKey (int /*<<< orphan*/ *,int,struct component_name*,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int min (size_t,size_t) ; 

__attribute__((used)) static int ciGetLeafPrefixKey(dtpage_t * lp, int li, dtpage_t * rp,
			       int ri, struct component_name * key, int flag)
{
	int klen, namlen;
	wchar_t *pl, *pr, *kname;
	struct component_name lkey;
	struct component_name rkey;

	lkey.name = kmalloc((JFS_NAME_MAX + 1) * sizeof(wchar_t),
					GFP_KERNEL);
	if (lkey.name == NULL)
		return -ENOMEM;

	rkey.name = kmalloc((JFS_NAME_MAX + 1) * sizeof(wchar_t),
					GFP_KERNEL);
	if (rkey.name == NULL) {
		kfree(lkey.name);
		return -ENOMEM;
	}

	/* get left and right key */
	dtGetKey(lp, li, &lkey, flag);
	lkey.name[lkey.namlen] = 0;

	if ((flag & JFS_OS2) == JFS_OS2)
		ciToUpper(&lkey);

	dtGetKey(rp, ri, &rkey, flag);
	rkey.name[rkey.namlen] = 0;


	if ((flag & JFS_OS2) == JFS_OS2)
		ciToUpper(&rkey);

	/* compute prefix */
	klen = 0;
	kname = key->name;
	namlen = min(lkey.namlen, rkey.namlen);
	for (pl = lkey.name, pr = rkey.name;
	     namlen; pl++, pr++, namlen--, klen++, kname++) {
		*kname = *pr;
		if (*pl != *pr) {
			key->namlen = klen + 1;
			goto free_names;
		}
	}

	/* l->namlen <= r->namlen since l <= r */
	if (lkey.namlen < rkey.namlen) {
		*kname = *pr;
		key->namlen = klen + 1;
	} else			/* l->namelen == r->namelen */
		key->namlen = klen;

free_names:
	kfree(lkey.name);
	kfree(rkey.name);
	return 0;
}