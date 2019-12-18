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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ H_AUTHORITY ; 
 int /*<<< orphan*/  ehea_error (char*,char*) ; 
 int /*<<< orphan*/  ehea_info (char*,char*) ; 

__attribute__((used)) static void ehea_promiscuous_error(u64 hret, int enable)
{
	if (hret == H_AUTHORITY)
		ehea_info("Hypervisor denied %sabling promiscuous mode",
			  enable == 1 ? "en" : "dis");
	else
		ehea_error("failed %sabling promiscuous mode",
			   enable == 1 ? "en" : "dis");
}