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
typedef  int /*<<< orphan*/  mach_zone_name_array_t ;
typedef  int /*<<< orphan*/  mach_zone_info_array_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  mach_memory_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

kern_return_t
mach_zone_info(
	host_priv_t		host,
	mach_zone_name_array_t	*namesp,
	mach_msg_type_number_t  *namesCntp,
	mach_zone_info_array_t	*infop,
	mach_msg_type_number_t  *infoCntp)
{
	return (mach_memory_info(host, namesp, namesCntp, infop, infoCntp, NULL, NULL));
}