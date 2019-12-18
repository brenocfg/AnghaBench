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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ hvc_iucv_filter ; 
 size_t hvc_iucv_filter_size ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int hvc_iucv_filter_connreq(u8 ipvmid[8])
{
	size_t i;

	/* Note: default policy is ACCEPT if no filter is set */
	if (!hvc_iucv_filter_size)
		return 0;

	for (i = 0; i < hvc_iucv_filter_size; i++)
		if (0 == memcmp(ipvmid, hvc_iucv_filter + (8 * i), 8))
			return 0;
	return 1;
}