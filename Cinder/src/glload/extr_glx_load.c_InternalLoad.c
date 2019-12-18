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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  ClearExtensionVars () ; 
 int /*<<< orphan*/  ProcExtsFromExtString (char const*) ; 
 scalar_t__ glXQueryExtensionsString (int /*<<< orphan*/ *,int) ; 
 int glx_LOAD_SUCCEEDED ; 

__attribute__((used)) static int InternalLoad(Display *display, int screen)
{
	ClearExtensionVars();
	
	
	ProcExtsFromExtString((const char *)glXQueryExtensionsString(display, screen));
	
	return glx_LOAD_SUCCEEDED;
}