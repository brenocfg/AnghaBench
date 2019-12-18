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
 int SHOWNEXTLOCDELAY ; 
 int /*<<< orphan*/  ShowNextLoc ; 
 int TICRATE ; 
 int /*<<< orphan*/  WI_initAnimatedBack () ; 
 scalar_t__ acceleratestage ; 
 int cnt ; 
 int /*<<< orphan*/  state ; 

void WI_initShowNextLoc(void)
{
    state = ShowNextLoc;
    acceleratestage = 0;
    cnt = SHOWNEXTLOCDELAY * TICRATE;

    WI_initAnimatedBack();
}