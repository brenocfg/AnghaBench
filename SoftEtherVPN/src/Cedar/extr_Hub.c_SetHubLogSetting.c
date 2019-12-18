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
typedef  int /*<<< orphan*/  HUB_LOG ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int /*<<< orphan*/  SetHubLogSettingEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void SetHubLogSetting(HUB *h, HUB_LOG *setting)
{
	SetHubLogSettingEx(h, setting, false);
}