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
struct mapped_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 scalar_t__ DM_TYPE_REQUEST_BASED ; 
 int EINVAL ; 
 scalar_t__ dm_get_md_type (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_init_request_based_queue (struct mapped_device*) ; 

int dm_setup_md_queue(struct mapped_device *md)
{
	if ((dm_get_md_type(md) == DM_TYPE_REQUEST_BASED) &&
	    !dm_init_request_based_queue(md)) {
		DMWARN("Cannot initialize queue for request-based mapped device");
		return -EINVAL;
	}

	return 0;
}