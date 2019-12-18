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
typedef  int /*<<< orphan*/  (* w1_slave_found_callback ) (struct w1_master*,int) ;
typedef  int u8 ;
typedef  int u64 ;
struct w1_master {int /*<<< orphan*/  dev; int /*<<< orphan*/  max_slave_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ w1_reset_bus (struct w1_master*) ; 
 int w1_triplet (struct w1_master*,int) ; 
 int /*<<< orphan*/  w1_write_8 (struct w1_master*,int) ; 

void w1_search(struct w1_master *dev, u8 search_type, w1_slave_found_callback cb)
{
	u64 last_rn, rn, tmp64;
	int i, slave_count = 0;
	int last_zero, last_device;
	int search_bit, desc_bit;
	u8  triplet_ret = 0;

	search_bit = 0;
	rn = last_rn = 0;
	last_device = 0;
	last_zero = -1;

	desc_bit = 64;

	while ( !last_device && (slave_count++ < dev->max_slave_count) ) {
		last_rn = rn;
		rn = 0;

		/*
		 * Reset bus and all 1-wire device state machines
		 * so they can respond to our requests.
		 *
		 * Return 0 - device(s) present, 1 - no devices present.
		 */
		if (w1_reset_bus(dev)) {
			dev_dbg(&dev->dev, "No devices present on the wire.\n");
			break;
		}

		/* Start the search */
		w1_write_8(dev, search_type);
		for (i = 0; i < 64; ++i) {
			/* Determine the direction/search bit */
			if (i == desc_bit)
				search_bit = 1;	  /* took the 0 path last time, so take the 1 path */
			else if (i > desc_bit)
				search_bit = 0;	  /* take the 0 path on the next branch */
			else
				search_bit = ((last_rn >> i) & 0x1);

			/** Read two bits and write one bit */
			triplet_ret = w1_triplet(dev, search_bit);

			/* quit if no device responded */
			if ( (triplet_ret & 0x03) == 0x03 )
				break;

			/* If both directions were valid, and we took the 0 path... */
			if (triplet_ret == 0)
				last_zero = i;

			/* extract the direction taken & update the device number */
			tmp64 = (triplet_ret >> 2);
			rn |= (tmp64 << i);

			if (kthread_should_stop()) {
				dev_dbg(&dev->dev, "Abort w1_search\n");
				return;
			}
		}

		if ( (triplet_ret & 0x03) != 0x03 ) {
			if ( (desc_bit == last_zero) || (last_zero < 0))
				last_device = 1;
			desc_bit = last_zero;
			cb(dev, rn);
		}
	}
}