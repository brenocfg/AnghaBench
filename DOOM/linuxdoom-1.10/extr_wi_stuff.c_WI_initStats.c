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
 int /*<<< orphan*/  StatCount ; 
 int /*<<< orphan*/  TICRATE ; 
 int /*<<< orphan*/  WI_initAnimatedBack () ; 
 scalar_t__ acceleratestage ; 
 int* cnt_items ; 
 int* cnt_kills ; 
 int cnt_par ; 
 int /*<<< orphan*/  cnt_pause ; 
 int* cnt_secret ; 
 int cnt_time ; 
 int sp_state ; 
 int /*<<< orphan*/  state ; 

void WI_initStats(void)
{
    state = StatCount;
    acceleratestage = 0;
    sp_state = 1;
    cnt_kills[0] = cnt_items[0] = cnt_secret[0] = -1;
    cnt_time = cnt_par = -1;
    cnt_pause = TICRATE;

    WI_initAnimatedBack();
}