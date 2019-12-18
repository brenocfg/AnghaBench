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
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  XP_MAX_NPARTITIONS_SN2 ; 
 int /*<<< orphan*/  is_shub () ; 
 int /*<<< orphan*/  sn_partition_id ; 
 int /*<<< orphan*/  sn_region_size ; 
 int /*<<< orphan*/  xp_cpu_to_nasid ; 
 int /*<<< orphan*/  xp_cpu_to_nasid_sn2 ; 
 int /*<<< orphan*/  xp_expand_memprotect ; 
 int /*<<< orphan*/  xp_expand_memprotect_sn2 ; 
 int /*<<< orphan*/  xp_max_npartitions ; 
 int /*<<< orphan*/  xp_pa ; 
 int /*<<< orphan*/  xp_pa_sn2 ; 
 int /*<<< orphan*/  xp_partition_id ; 
 int /*<<< orphan*/  xp_region_size ; 
 int xp_register_nofault_code_sn2 () ; 
 int /*<<< orphan*/  xp_remote_memcpy ; 
 int /*<<< orphan*/  xp_remote_memcpy_sn2 ; 
 int /*<<< orphan*/  xp_restrict_memprotect ; 
 int /*<<< orphan*/  xp_restrict_memprotect_sn2 ; 
 int /*<<< orphan*/  xp_socket_pa ; 
 int /*<<< orphan*/  xp_socket_pa_sn2 ; 

enum xp_retval
xp_init_sn2(void)
{
	BUG_ON(!is_shub());

	xp_max_npartitions = XP_MAX_NPARTITIONS_SN2;
	xp_partition_id = sn_partition_id;
	xp_region_size = sn_region_size;

	xp_pa = xp_pa_sn2;
	xp_socket_pa = xp_socket_pa_sn2;
	xp_remote_memcpy = xp_remote_memcpy_sn2;
	xp_cpu_to_nasid = xp_cpu_to_nasid_sn2;
	xp_expand_memprotect = xp_expand_memprotect_sn2;
	xp_restrict_memprotect = xp_restrict_memprotect_sn2;

	return xp_register_nofault_code_sn2();
}