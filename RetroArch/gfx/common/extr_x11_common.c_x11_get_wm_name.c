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
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  False ; 
 scalar_t__ Success ; 
 int /*<<< orphan*/  XA_WINDOW ; 
 int /*<<< orphan*/  XFree (unsigned char*) ; 
 scalar_t__ XGetWindowProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,unsigned long*,unsigned long*,unsigned char**) ; 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 char* strdup (char*) ; 

char *x11_get_wm_name(Display *dpy)
{
   Atom type;
   int  format;
   Window window;
   Atom XA_NET_SUPPORTING_WM_CHECK = XInternAtom(g_x11_dpy, "_NET_SUPPORTING_WM_CHECK", False);
   Atom XA_NET_WM_NAME             = XInternAtom(g_x11_dpy, "_NET_WM_NAME", False);
   Atom XA_UTF8_STRING             = XInternAtom(g_x11_dpy, "UTF8_STRING", False);
   unsigned long nitems            = 0;
   unsigned long bytes_after       = 0;
   char *title                     = NULL;
   unsigned char *propdata         = NULL;

   if (!XA_NET_SUPPORTING_WM_CHECK || !XA_NET_WM_NAME)
      return NULL;

   if (!(XGetWindowProperty(dpy,
                               DefaultRootWindow(dpy),
                               XA_NET_SUPPORTING_WM_CHECK,
                               0,
                               1,
                               False,
                               XA_WINDOW,
                               &type,
                               &format,
                               &nitems,
                               &bytes_after,
                               &propdata) == Success &&
		   propdata))
	   return NULL;

   window = ((Window *) propdata)[0];

   XFree(propdata);

   if (!(XGetWindowProperty(dpy,
                               window,
                               XA_NET_WM_NAME,
                               0,
                               8192,
                               False,
                               XA_UTF8_STRING,
                               &type,
                               &format,
                               &nitems,
                               &bytes_after,
                               &propdata) == Success
		   && propdata))
	   return NULL;

   title = strdup((char *) propdata);
   XFree(propdata);

   return title;
}