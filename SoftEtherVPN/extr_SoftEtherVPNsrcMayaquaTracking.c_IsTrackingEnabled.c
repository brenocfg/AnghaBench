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

/* Variables and functions */
 scalar_t__ IsDebug () ; 
 scalar_t__ IsMemCheck () ; 
 scalar_t__ kernel_status_inited ; 

bool IsTrackingEnabled()
{
	return (IsDebug() || IsMemCheck()) && kernel_status_inited;
}