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
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 TYPE_1__ g_last_storage_ip ; 
 int /*<<< orphan*/  g_storage_ip_changed_auto_adjust ; 
 scalar_t__ g_use_storage_id ; 
 int storage_changelog_req () ; 
 int storage_report_storage_ip_addr () ; 

int storage_check_ip_changed()
{
	int result;

	if ((!g_storage_ip_changed_auto_adjust) || g_use_storage_id)
	{
		return 0;
	}

	if ((result=storage_report_storage_ip_addr()) != 0)
	{
		return result;
	}

	if (g_last_storage_ip.count == 0) //first run
	{
		return 0;
	}

	return storage_changelog_req();
}