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
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IFRTYPE_QOSMARKING_FASTLANE ; 
 int /*<<< orphan*/  IFRTYPE_QOSMARKING_MODE_NONE ; 
 int /*<<< orphan*/  if_set_qosmarking_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

errno_t
ifnet_set_fastlane_capable(ifnet_t interface, boolean_t capable)
{
	if (interface == NULL)
		return (EINVAL);

	if_set_qosmarking_mode(interface,
	    capable ? IFRTYPE_QOSMARKING_FASTLANE : IFRTYPE_QOSMARKING_MODE_NONE);

	return (0);
}