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
 int /*<<< orphan*/ * helpline_fns ; 
 int /*<<< orphan*/  tui_helpline_fns ; 
 int /*<<< orphan*/  ui_helpline__puts (char*) ; 

void ui_helpline__init(void)
{
	helpline_fns = &tui_helpline_fns;
	ui_helpline__puts(" ");
}