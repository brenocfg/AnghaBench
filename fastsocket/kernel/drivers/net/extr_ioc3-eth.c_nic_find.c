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
typedef  unsigned long u64 ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int nic_read_bit (struct ioc3*) ; 
 int /*<<< orphan*/  nic_reset (struct ioc3*) ; 
 int /*<<< orphan*/  nic_write_bit (struct ioc3*,int) ; 
 int /*<<< orphan*/  nic_write_byte (struct ioc3*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static u64 nic_find(struct ioc3 *ioc3, int *last)
{
	int a, b, index, disc;
	u64 address = 0;

	nic_reset(ioc3);
	/* Search ROM.  */
	nic_write_byte(ioc3, 0xf0);

	/* Algorithm from ``Book of iButton Standards''.  */
	for (index = 0, disc = 0; index < 64; index++) {
		a = nic_read_bit(ioc3);
		b = nic_read_bit(ioc3);

		if (a && b) {
			printk("NIC search failed (not fatal).\n");
			*last = 0;
			return 0;
		}

		if (!a && !b) {
			if (index == *last) {
				address |= 1UL << index;
			} else if (index > *last) {
				address &= ~(1UL << index);
				disc = index;
			} else if ((address & (1UL << index)) == 0)
				disc = index;
			nic_write_bit(ioc3, address & (1UL << index));
			continue;
		} else {
			if (a)
				address |= 1UL << index;
			else
				address &= ~(1UL << index);
			nic_write_bit(ioc3, a);
			continue;
		}
	}

	*last = disc;

	return address;
}