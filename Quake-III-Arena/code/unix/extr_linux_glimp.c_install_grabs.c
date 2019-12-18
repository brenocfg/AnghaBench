#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vidWidth; int vidHeight; } ;
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Cvar_Set ) (char*,char*) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CreateNullCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  GrabModeAsync ; 
 int /*<<< orphan*/  MOUSE_MASK ; 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  Sys_Milliseconds () ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XChangePointerControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XF86DGADirectMouse ; 
 int /*<<< orphan*/  XF86DGADirectVideo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XF86DGAQueryVersion (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  XGetPointerControl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XGrabKeyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGrabPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XWarpPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dpy ; 
 TYPE_3__ glConfig ; 
 TYPE_2__* in_dgamouse ; 
 int /*<<< orphan*/  mouseResetTime ; 
 int /*<<< orphan*/  mouse_accel_denominator ; 
 int /*<<< orphan*/  mouse_accel_numerator ; 
 int /*<<< orphan*/  mouse_threshold ; 
 int mwx ; 
 int mwy ; 
 scalar_t__ mx ; 
 scalar_t__ my ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (char*,char*) ; 
 int /*<<< orphan*/  win ; 

__attribute__((used)) static void install_grabs(void)
{
  // inviso cursor
  XWarpPointer(dpy, None, win,
               0, 0, 0, 0,
               glConfig.vidWidth / 2, glConfig.vidHeight / 2);
  XSync(dpy, False);

  XDefineCursor(dpy, win, CreateNullCursor(dpy, win));

  XGrabPointer(dpy, win, // bk010108 - do this earlier?
               False,
               MOUSE_MASK,
               GrabModeAsync, GrabModeAsync,
               win,
               None,
               CurrentTime);

  XGetPointerControl(dpy, &mouse_accel_numerator, &mouse_accel_denominator,
                     &mouse_threshold);

  XChangePointerControl(dpy, True, True, 1, 1, 0);

  XSync(dpy, False);

  mouseResetTime = Sys_Milliseconds ();

  if (in_dgamouse->value)
  {
    int MajorVersion, MinorVersion;

    if (!XF86DGAQueryVersion(dpy, &MajorVersion, &MinorVersion))
    {
      // unable to query, probalby not supported, force the setting to 0
      ri.Printf( PRINT_ALL, "Failed to detect XF86DGA Mouse\n" );
      ri.Cvar_Set( "in_dgamouse", "0" );
    } else
    {
      XF86DGADirectVideo(dpy, DefaultScreen(dpy), XF86DGADirectMouse);
      XWarpPointer(dpy, None, win, 0, 0, 0, 0, 0, 0);
    }
  } else
  {
    mwx = glConfig.vidWidth / 2;
    mwy = glConfig.vidHeight / 2;
    mx = my = 0;
  }

  XGrabKeyboard(dpy, win,
                False,
                GrabModeAsync, GrabModeAsync,
                CurrentTime);

  XSync(dpy, False);
}