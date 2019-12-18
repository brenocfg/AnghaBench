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
struct dwarf_cie {unsigned long length; unsigned long cie_pointer; char version; char* augmentation; unsigned int code_alignment_factor; unsigned int return_address_reg; char encoding; unsigned char* instructions_end; int /*<<< orphan*/  link; void* initial_instructions; int /*<<< orphan*/  flags; int /*<<< orphan*/  data_alignment_factor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_CIE_Z_AUGMENTATION ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UNWINDER_BUG () ; 
 int /*<<< orphan*/  UNWINDER_BUG_ON (int) ; 
 unsigned int __raw_readb (void*) ; 
 int /*<<< orphan*/  dwarf_cie_list ; 
 int /*<<< orphan*/  dwarf_cie_lock ; 
 int dwarf_read_leb128 (void*,int /*<<< orphan*/ *) ; 
 void* dwarf_read_uleb128 (void*,unsigned int*) ; 
 struct dwarf_cie* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int dwarf_parse_cie(void *entry, void *p, unsigned long len,
			   unsigned char *end)
{
	struct dwarf_cie *cie;
	unsigned long flags;
	int count;

	cie = kzalloc(sizeof(*cie), GFP_KERNEL);
	if (!cie)
		return -ENOMEM;

	cie->length = len;

	/*
	 * Record the offset into the .eh_frame section
	 * for this CIE. It allows this CIE to be
	 * quickly and easily looked up from the
	 * corresponding FDE.
	 */
	cie->cie_pointer = (unsigned long)entry;

	cie->version = *(char *)p++;
	UNWINDER_BUG_ON(cie->version != 1);

	cie->augmentation = p;
	p += strlen(cie->augmentation) + 1;

	count = dwarf_read_uleb128(p, &cie->code_alignment_factor);
	p += count;

	count = dwarf_read_leb128(p, &cie->data_alignment_factor);
	p += count;

	/*
	 * Which column in the rule table contains the
	 * return address?
	 */
	if (cie->version == 1) {
		cie->return_address_reg = __raw_readb(p);
		p++;
	} else {
		count = dwarf_read_uleb128(p, &cie->return_address_reg);
		p += count;
	}

	if (cie->augmentation[0] == 'z') {
		unsigned int length, count;
		cie->flags |= DWARF_CIE_Z_AUGMENTATION;

		count = dwarf_read_uleb128(p, &length);
		p += count;

		UNWINDER_BUG_ON((unsigned char *)p > end);

		cie->initial_instructions = p + length;
		cie->augmentation++;
	}

	while (*cie->augmentation) {
		/*
		 * "L" indicates a byte showing how the
		 * LSDA pointer is encoded. Skip it.
		 */
		if (*cie->augmentation == 'L') {
			p++;
			cie->augmentation++;
		} else if (*cie->augmentation == 'R') {
			/*
			 * "R" indicates a byte showing
			 * how FDE addresses are
			 * encoded.
			 */
			cie->encoding = *(char *)p++;
			cie->augmentation++;
		} else if (*cie->augmentation == 'P') {
			/*
			 * "R" indicates a personality
			 * routine in the CIE
			 * augmentation.
			 */
			UNWINDER_BUG();
		} else if (*cie->augmentation == 'S') {
			UNWINDER_BUG();
		} else {
			/*
			 * Unknown augmentation. Assume
			 * 'z' augmentation.
			 */
			p = cie->initial_instructions;
			UNWINDER_BUG_ON(!p);
			break;
		}
	}

	cie->initial_instructions = p;
	cie->instructions_end = end;

	/* Add to list */
	spin_lock_irqsave(&dwarf_cie_lock, flags);
	list_add_tail(&cie->link, &dwarf_cie_list);
	spin_unlock_irqrestore(&dwarf_cie_lock, flags);

	return 0;
}