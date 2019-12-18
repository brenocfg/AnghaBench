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
struct TYPE_3__ {int /*<<< orphan*/  minor_code; int /*<<< orphan*/  request_code; int /*<<< orphan*/  error_code; } ;
typedef  TYPE_1__ XErrorEvent ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_WARN (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGetErrorText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int x_log_error_handler(Display *dpy, XErrorEvent *event)
{
   char buf[1024];
   XGetErrorText(dpy, event->error_code, buf, sizeof buf);
   RARCH_WARN("[GLX]: X error message: %s, request code: %d, minor code: %d\n",
         buf, event->request_code, event->minor_code);
   return 0;
}