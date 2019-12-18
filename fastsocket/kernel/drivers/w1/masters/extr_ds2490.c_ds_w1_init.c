#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct w1_bus_master {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * set_pullup; int /*<<< orphan*/ * reset_bus; int /*<<< orphan*/ * write_block; int /*<<< orphan*/ * read_block; int /*<<< orphan*/ * write_byte; int /*<<< orphan*/ * read_byte; int /*<<< orphan*/ * touch_bit; struct ds_device* data; } ;
struct ds_device {TYPE_1__ master; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds9490r_read_block ; 
 int /*<<< orphan*/  ds9490r_read_byte ; 
 int /*<<< orphan*/  ds9490r_reset ; 
 int /*<<< orphan*/  ds9490r_set_pullup ; 
 int /*<<< orphan*/  ds9490r_touch_bit ; 
 int /*<<< orphan*/  ds9490r_write_block ; 
 int /*<<< orphan*/  ds9490r_write_byte ; 
 int /*<<< orphan*/  ds_reset_device (struct ds_device*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int w1_add_master_device (TYPE_1__*) ; 

__attribute__((used)) static int ds_w1_init(struct ds_device *dev)
{
	memset(&dev->master, 0, sizeof(struct w1_bus_master));

	/* Reset the device as it can be in a bad state.
	 * This is necessary because a block write will wait for data
	 * to be placed in the output buffer and block any later
	 * commands which will keep accumulating and the device will
	 * not be idle.  Another case is removing the ds2490 module
	 * while a bus search is in progress, somehow a few commands
	 * get through, but the input transfers fail leaving data in
	 * the input buffer.  This will cause the next read to fail
	 * see the note in ds_recv_data.
	 */
	ds_reset_device(dev);

	dev->master.data	= dev;
	dev->master.touch_bit	= &ds9490r_touch_bit;
	/* read_bit and write_bit in w1_bus_master are expected to set and
	 * sample the line level.  For write_bit that means it is expected to
	 * set it to that value and leave it there.  ds2490 only supports an
	 * individual time slot at the lowest level.  The requirement from
	 * pulling the bus state down to reading the state is 15us, something
	 * that isn't realistic on the USB bus anyway.
	dev->master.read_bit	= &ds9490r_read_bit;
	dev->master.write_bit	= &ds9490r_write_bit;
	*/
	dev->master.read_byte	= &ds9490r_read_byte;
	dev->master.write_byte	= &ds9490r_write_byte;
	dev->master.read_block	= &ds9490r_read_block;
	dev->master.write_block	= &ds9490r_write_block;
	dev->master.reset_bus	= &ds9490r_reset;
	dev->master.set_pullup	= &ds9490r_set_pullup;

	return w1_add_master_device(&dev->master);
}