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
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  host_t ;
typedef  scalar_t__ host_priv_t ;
typedef  int /*<<< orphan*/  host_info_t ;
typedef  int /*<<< orphan*/  host_flavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  host_statistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
host_priv_statistics(host_priv_t host_priv, host_flavor_t flavor, host_info_t info, mach_msg_type_number_t * count)
{
	return (host_statistics((host_t)host_priv, flavor, info, count));
}