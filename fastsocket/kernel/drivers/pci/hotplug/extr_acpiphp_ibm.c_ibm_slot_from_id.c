#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int slot_num; } ;
struct TYPE_5__ {int type; size_t len; } ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/  sig; } ;
union apci_descriptor {TYPE_3__ slot; TYPE_2__ generic; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ibm_get_table_from_acpi (char**) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 union apci_descriptor* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (union apci_descriptor*,union apci_descriptor*,int) ; 

__attribute__((used)) static union apci_descriptor *ibm_slot_from_id(int id)
{
	int ind = 0, size;
	union apci_descriptor *ret = NULL, *des;
	char *table;

	size = ibm_get_table_from_acpi(&table);
	des = (union apci_descriptor *)table;
	if (memcmp(des->header.sig, "aPCI", 4) != 0)
		goto ibm_slot_done;

	des = (union apci_descriptor *)&table[ind += des->header.len];
	while (ind < size && (des->generic.type != 0x82 ||
			des->slot.slot_num != id)) {
		des = (union apci_descriptor *)&table[ind += des->generic.len];
	}

	if (ind < size && des->slot.slot_num == id)
		ret = des;

ibm_slot_done:
	if (ret) {
		ret = kmalloc(sizeof(union apci_descriptor), GFP_KERNEL);
		memcpy(ret, des, sizeof(union apci_descriptor));
	}
	kfree(table);
	return ret;
}