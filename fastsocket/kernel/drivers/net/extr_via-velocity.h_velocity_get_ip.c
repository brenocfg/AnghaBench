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
struct velocity_info {int /*<<< orphan*/  ip_addr; TYPE_1__* dev; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_address; } ;
struct in_device {scalar_t__ ifa_list; } ;
struct TYPE_2__ {scalar_t__ ip_ptr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int velocity_get_ip(struct velocity_info *vptr)
{
	struct in_device *in_dev = (struct in_device *) vptr->dev->ip_ptr;
	struct in_ifaddr *ifa;

	if (in_dev != NULL) {
		ifa = (struct in_ifaddr *) in_dev->ifa_list;
		if (ifa != NULL) {
			memcpy(vptr->ip_addr, &ifa->ifa_address, 4);
			return 0;
		}
	}
	return -ENOENT;
}