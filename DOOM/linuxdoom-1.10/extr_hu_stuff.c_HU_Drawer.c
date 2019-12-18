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
 int /*<<< orphan*/  HUlib_drawIText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUlib_drawSText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUlib_drawTextLine (int /*<<< orphan*/ *,int) ; 
 scalar_t__ automapactive ; 
 int /*<<< orphan*/  w_chat ; 
 int /*<<< orphan*/  w_message ; 
 int /*<<< orphan*/  w_title ; 

void HU_Drawer(void)
{

    HUlib_drawSText(&w_message);
    HUlib_drawIText(&w_chat);
    if (automapactive)
	HUlib_drawTextLine(&w_title, false);

}