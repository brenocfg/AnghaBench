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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HDAPS_PORT_KMACT ; 
 int HDAPS_X_AXIS ; 
 int HDAPS_Y_AXIS ; 
 int /*<<< orphan*/  __device_complete () ; 
 scalar_t__ __device_refresh_sync () ; 
 int hdaps_invert ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int inw (unsigned int) ; 
 int /*<<< orphan*/  km_activity ; 

__attribute__((used)) static int __hdaps_read_pair(unsigned int port1, unsigned int port2,
			     int *x, int *y)
{
	/* do a sync refresh -- we need to be sure that we read fresh data */
	if (__device_refresh_sync())
		return -EIO;

	*y = inw(port2);
	*x = inw(port1);
	km_activity = inb(HDAPS_PORT_KMACT);
	__device_complete();

	/* hdaps_invert is a bitvector to negate the axes */
	if (hdaps_invert & HDAPS_X_AXIS)
		*x = -*x;
	if (hdaps_invert & HDAPS_Y_AXIS)
		*y = -*y;

	return 0;
}