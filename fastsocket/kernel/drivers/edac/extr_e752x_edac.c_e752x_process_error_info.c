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
typedef  int u32 ;
struct mem_ctl_info {int dummy; } ;
struct e752x_error_info {int ferr_global; int nerr_global; } ;

/* Variables and functions */
 int /*<<< orphan*/  e752x_check_dram (struct mem_ctl_info*,struct e752x_error_info*,int*,int) ; 
 int /*<<< orphan*/  e752x_check_hub_interface (struct e752x_error_info*,int*,int) ; 
 int /*<<< orphan*/  e752x_check_membuf (struct e752x_error_info*,int*,int) ; 
 int /*<<< orphan*/  e752x_check_ns_interface (struct e752x_error_info*,int*,int) ; 
 int /*<<< orphan*/  e752x_check_sysbus (struct e752x_error_info*,int*,int) ; 
 int /*<<< orphan*/  global_error (int,int,int*,int) ; 

__attribute__((used)) static int e752x_process_error_info(struct mem_ctl_info *mci,
				struct e752x_error_info *info,
				int handle_errors)
{
	u32 error32, stat32;
	int error_found;

	error_found = 0;
	error32 = (info->ferr_global >> 18) & 0x3ff;
	stat32 = (info->ferr_global >> 4) & 0x7ff;

	if (error32)
		global_error(1, error32, &error_found, handle_errors);

	if (stat32)
		global_error(0, stat32, &error_found, handle_errors);

	error32 = (info->nerr_global >> 18) & 0x3ff;
	stat32 = (info->nerr_global >> 4) & 0x7ff;

	if (error32)
		global_error(1, error32, &error_found, handle_errors);

	if (stat32)
		global_error(0, stat32, &error_found, handle_errors);

	e752x_check_hub_interface(info, &error_found, handle_errors);
	e752x_check_ns_interface(info, &error_found, handle_errors);
	e752x_check_sysbus(info, &error_found, handle_errors);
	e752x_check_membuf(info, &error_found, handle_errors);
	e752x_check_dram(mci, info, &error_found, handle_errors);
	return error_found;
}