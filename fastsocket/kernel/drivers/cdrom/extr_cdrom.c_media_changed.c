#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cdrom_device_info {unsigned int mc_flags; scalar_t__ media_written; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* media_changed ) (struct cdrom_device_info*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_MEDIA_CHANGED ; 
 int /*<<< orphan*/  CDROM_CAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDSL_CURRENT ; 
 scalar_t__ stub1 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int media_changed(struct cdrom_device_info *cdi, int queue)
{
	unsigned int mask = (1 << (queue & 1));
	int ret = !!(cdi->mc_flags & mask);

	if (!CDROM_CAN(CDC_MEDIA_CHANGED))
	    return ret;
	/* changed since last call? */
	if (cdi->ops->media_changed(cdi, CDSL_CURRENT)) {
		cdi->mc_flags = 0x3;    /* set bit on both queues */
		ret |= 1;
		cdi->media_written = 0;
	}
	cdi->mc_flags &= ~mask;         /* clear bit */
	return ret;
}