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
struct TYPE_3__ {char* res_name; char* res_class; } ;
typedef  TYPE_1__ XClassHint ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  XSetClassHint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void x11_set_window_class(Display *dpy, Window win)
{
   XClassHint hint;

   hint.res_name   = (char*)"retroarch"; /* Broken header. */
   hint.res_class  = (char*)"retroarch";
   XSetClassHint(dpy, win, &hint);
}