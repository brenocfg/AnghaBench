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
typedef  void* u32 ;
struct dwarf_fde {unsigned long length; unsigned long cie_pointer; unsigned char* end; int /*<<< orphan*/  link; void* instructions; struct dwarf_cie* cie; int /*<<< orphan*/  address_range; int /*<<< orphan*/  initial_location; } ;
struct dwarf_cie {int encoding; int flags; } ;

/* Variables and functions */
 int DWARF_CIE_Z_AUGMENTATION ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dwarf_fde_list ; 
 int /*<<< orphan*/  dwarf_fde_lock ; 
 struct dwarf_cie* dwarf_lookup_cie (unsigned long) ; 
 int dwarf_read_addr (void*,int /*<<< orphan*/ *) ; 
 int dwarf_read_encoded_value (void*,int /*<<< orphan*/ *,int) ; 
 int dwarf_read_uleb128 (void*,unsigned int*) ; 
 struct dwarf_fde* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwarf_parse_fde(void *entry, u32 entry_type,
			   void *start, unsigned long len,
			   unsigned char *end)
{
	struct dwarf_fde *fde;
	struct dwarf_cie *cie;
	unsigned long flags;
	int count;
	void *p = start;

	fde = kzalloc(sizeof(*fde), GFP_KERNEL);
	if (!fde)
		return -ENOMEM;

	fde->length = len;

	/*
	 * In a .eh_frame section the CIE pointer is the
	 * delta between the address within the FDE
	 */
	fde->cie_pointer = (unsigned long)(p - entry_type - 4);

	cie = dwarf_lookup_cie(fde->cie_pointer);
	fde->cie = cie;

	if (cie->encoding)
		count = dwarf_read_encoded_value(p, &fde->initial_location,
						 cie->encoding);
	else
		count = dwarf_read_addr(p, &fde->initial_location);

	p += count;

	if (cie->encoding)
		count = dwarf_read_encoded_value(p, &fde->address_range,
						 cie->encoding & 0x0f);
	else
		count = dwarf_read_addr(p, &fde->address_range);

	p += count;

	if (fde->cie->flags & DWARF_CIE_Z_AUGMENTATION) {
		unsigned int length;
		count = dwarf_read_uleb128(p, &length);
		p += count + length;
	}

	/* Call frame instructions. */
	fde->instructions = p;
	fde->end = end;

	/* Add to list. */
	spin_lock_irqsave(&dwarf_fde_lock, flags);
	list_add_tail(&fde->link, &dwarf_fde_list);
	spin_unlock_irqrestore(&dwarf_fde_lock, flags);

	return 0;
}