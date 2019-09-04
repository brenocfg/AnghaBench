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
typedef  int UINT ;

/* Variables and functions */
 int DISK_FREE_CHECK_INTERVAL_DEFAULT ; 
 int eraser_check_interval ; 

void SetEraserCheckInterval(UINT interval)
{
	if (interval == 0)
	{
		eraser_check_interval = DISK_FREE_CHECK_INTERVAL_DEFAULT;
	}
	else
	{
		eraser_check_interval = interval * 1000;
	}
}