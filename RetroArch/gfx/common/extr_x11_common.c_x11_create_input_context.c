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
typedef  int /*<<< orphan*/  XIM ;
typedef  int /*<<< orphan*/  XIC ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  XCreateIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int XIMPreeditNothing ; 
 int XIMStatusNothing ; 
 int /*<<< orphan*/  XNClientWindow ; 
 int /*<<< orphan*/  XNInputStyle ; 
 int /*<<< orphan*/  XOpenIM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSetICFocus (int /*<<< orphan*/ ) ; 
 int g_x11_has_focus ; 
 int /*<<< orphan*/  x11_destroy_input_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool x11_create_input_context(Display *dpy, Window win, XIM *xim, XIC *xic)
{
   x11_destroy_input_context(xim, xic);

   g_x11_has_focus = true;
   *xim            = XOpenIM(dpy, NULL, NULL, NULL);

   if (!*xim)
   {
      RARCH_ERR("[X11]: Failed to open input method.\n");
      return false;
   }

   *xic = XCreateIC(*xim, XNInputStyle,
         XIMPreeditNothing | XIMStatusNothing, XNClientWindow, win, NULL);

   if (!*xic)
   {
      RARCH_ERR("[X11]: Failed to create input context.\n");
      return false;
   }

   XSetICFocus(*xic);
   return true;
}