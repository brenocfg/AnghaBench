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
typedef  int u_char ;
struct mca_device {int dummy; } ;
typedef  int ibmlana_medium ;

/* Variables and functions */
 int mca_device_read_stored_pos (struct mca_device*,int) ; 

__attribute__((used)) static void getaddrs(struct mca_device *mdev, int *base, int *memlen,
		     int *iobase, int *irq, ibmlana_medium *medium)
{
	u_char pos0, pos1;

	pos0 = mca_device_read_stored_pos(mdev, 2);
	pos1 = mca_device_read_stored_pos(mdev, 3);

	*base = 0xc0000 + ((pos1 & 0xf0) << 9);
	*memlen = (pos1 & 0x01) ? 0x8000 : 0x4000;
	*iobase = (pos0 & 0xe0) << 7;
	switch (pos0 & 0x06) {
	case 0:
		*irq = 5;
		break;
	case 2:
		*irq = 15;
		break;
	case 4:
		*irq = 10;
		break;
	case 6:
		*irq = 11;
		break;
	}
	*medium = (pos0 & 0x18) >> 3;
}