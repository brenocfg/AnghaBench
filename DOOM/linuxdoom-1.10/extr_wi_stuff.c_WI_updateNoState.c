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
 int /*<<< orphan*/  G_WorldDone () ; 
 int /*<<< orphan*/  WI_End () ; 
 int /*<<< orphan*/  WI_updateAnimatedBack () ; 
 int /*<<< orphan*/  cnt ; 

void WI_updateNoState(void) {

    WI_updateAnimatedBack();

    if (!--cnt)
    {
	WI_End();
	G_WorldDone();
    }

}