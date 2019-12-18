#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
struct TYPE_6__ {int noutput; int /*<<< orphan*/ * outputs; } ;
typedef  TYPE_1__ XRRScreenResources ;
struct TYPE_7__ {char* name; } ;
typedef  TYPE_2__ XRROutputInfo ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ *) ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ ) ; 
 TYPE_2__* XRRGetOutputInfo (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* XRRGetScreenResources (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

const char *x11_display_server_get_output_options(void *data)
{
#ifdef HAVE_XRANDR
   Display *dpy;
   XRRScreenResources *res;
   XRROutputInfo *info;
   Window root;
   int i;
   static char s[PATH_MAX_LENGTH];

   if (!(dpy = XOpenDisplay(0)))
      return NULL;

   root = RootWindow(dpy, DefaultScreen(dpy));

   if (!(res = XRRGetScreenResources(dpy, root)))
      return NULL;

   for (i = 0; i < res->noutput; i++)
   {
      if (!(info = XRRGetOutputInfo(dpy, res, res->outputs[i])))
         return NULL;

      strlcat(s, info->name, sizeof(s));
      if ((i+1) < res->noutput)
         strlcat(s, "|", sizeof(s));
   }

   return s;
#else
   /* TODO/FIXME - hardcoded for now; list should be built up dynamically later */
   return "HDMI-0|HDMI-1|HDMI-2|HDMI-3|DVI-0|DVI-1|DVI-2|DVI-3|VGA-0|VGA-1|VGA-2|VGA-3|Config";
#endif
}