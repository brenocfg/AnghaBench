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
typedef  int u8 ;
struct bus_node {int /*<<< orphan*/  rangePFMem; int /*<<< orphan*/  rangeMem; int /*<<< orphan*/  rangeIO; } ;
struct bus_info {int slot_max; int slot_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 struct bus_node* ibmphp_find_res_bus (int) ; 
 struct bus_info* ibmphp_find_same_bus_num (int) ; 

__attribute__((used)) static u8 find_sec_number (u8 primary_busno, u8 slotno)
{
	int min, max;
	u8 busno;
	struct bus_info *bus;
	struct bus_node *bus_cur;

	bus = ibmphp_find_same_bus_num (primary_busno);
	if (!bus) {
		err ("cannot get slot range of the bus from the BIOS\n");
		return 0xff;
	}
	max = bus->slot_max;
	min = bus->slot_min;
	if ((slotno > max) || (slotno < min)) {
		err ("got the wrong range\n");
		return 0xff;
	}
	busno = (u8) (slotno - (u8) min);
	busno += primary_busno + 0x01;
	bus_cur = ibmphp_find_res_bus (busno);
	/* either there is no such bus number, or there are no ranges, which
	 * can only happen if we removed the bridged device in previous load
	 * of the driver, and now only have the skeleton bus struct
	 */
	if ((!bus_cur) || (!(bus_cur->rangeIO) && !(bus_cur->rangeMem) && !(bus_cur->rangePFMem)))
		return busno;
	return 0xff;
}