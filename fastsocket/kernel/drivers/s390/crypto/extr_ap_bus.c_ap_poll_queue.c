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
struct ap_device {int dummy; } ;

/* Variables and functions */
 int ap_poll_read (struct ap_device*,unsigned long*) ; 
 int ap_poll_write (struct ap_device*,unsigned long*) ; 

__attribute__((used)) static inline int ap_poll_queue(struct ap_device *ap_dev, unsigned long *flags)
{
	int rc;

	rc = ap_poll_read(ap_dev, flags);
	if (rc)
		return rc;
	return ap_poll_write(ap_dev, flags);
}