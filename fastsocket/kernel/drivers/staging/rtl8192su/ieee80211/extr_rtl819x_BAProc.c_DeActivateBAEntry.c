#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_device {int dummy; } ;
struct TYPE_3__ {int bValid; int /*<<< orphan*/  Timer; } ;
typedef  TYPE_1__* PBA_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void DeActivateBAEntry( struct ieee80211_device* ieee, PBA_RECORD pBA)
{
	pBA->bValid = false;
	del_timer_sync(&pBA->Timer);
}