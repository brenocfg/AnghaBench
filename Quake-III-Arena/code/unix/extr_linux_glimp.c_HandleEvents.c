#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_16__ {int button; } ;
struct TYPE_12__ {int /*<<< orphan*/  time; } ;
struct TYPE_15__ {int x_root; int y_root; int x; int y; } ;
struct TYPE_17__ {int type; TYPE_2__ xconfigure; TYPE_1__ xcreatewindow; TYPE_4__ xbutton; TYPE_11__ xkey; TYPE_3__ xmotion; } ;
typedef  TYPE_5__ XEvent ;
struct TYPE_20__ {int /*<<< orphan*/  keyCatchers; } ;
struct TYPE_19__ {int vidWidth; int vidHeight; } ;
struct TYPE_18__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
#define  ButtonPress 134 
#define  ButtonRelease 133 
#define  ConfigureNotify 132 
#define  CreateNotify 131 
 int /*<<< orphan*/  K_MOUSE1 ; 
 int K_MWHEELDOWN ; 
 int K_MWHEELUP ; 
#define  KeyPress 130 
#define  KeyRelease 129 
 int /*<<< orphan*/  MOUSE_RESET_DELAY ; 
#define  MotionNotify 128 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  SE_CHAR ; 
 int /*<<< orphan*/  SE_KEY ; 
 int /*<<< orphan*/  SE_MOUSE ; 
 int /*<<< orphan*/  Sys_QueEvent (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int Sys_XTimeToSysTime (int /*<<< orphan*/ ) ; 
 char* XLateKey (TYPE_11__*,int*) ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ XPending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XWarpPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int abs (int) ; 
 TYPE_9__ cls ; 
 int /*<<< orphan*/  dpy ; 
 TYPE_8__ glConfig ; 
 TYPE_7__* in_dgamouse ; 
 int /*<<< orphan*/  mouseResetTime ; 
 int /*<<< orphan*/  mouse_active ; 
 int mwx ; 
 int mwy ; 
 int mx ; 
 int my ; 
 int qfalse ; 
 int qtrue ; 
 int repeated_press (TYPE_5__*) ; 
 int /*<<< orphan*/  win ; 
 int /*<<< orphan*/  win_x ; 
 int /*<<< orphan*/  win_y ; 

__attribute__((used)) static void HandleEvents(void)
{
  int b;
  int key;
  XEvent event;
  qboolean dowarp = qfalse;
  char *p;
  int dx, dy;
  int t = 0; // default to 0 in case we don't set
	
  if (!dpy)
    return;

  while (XPending(dpy))
  {
    XNextEvent(dpy, &event);
    switch (event.type)
    {
    case KeyPress:
			t = Sys_XTimeToSysTime(event.xkey.time);
      p = XLateKey(&event.xkey, &key);
      if (key)
      {
        Sys_QueEvent( t, SE_KEY, key, qtrue, 0, NULL );
      }
      if (p)
      {
        while (*p)
        {
          Sys_QueEvent( t, SE_CHAR, *p++, 0, 0, NULL );
        }
      }
      break;

    case KeyRelease:
			t = Sys_XTimeToSysTime(event.xkey.time);
      // bk001206 - handle key repeat w/o XAutRepatOn/Off
      //            also: not done if console/menu is active.
      // From Ryan's Fakk2.
      // see game/q_shared.h, KEYCATCH_* . 0 == in 3d game.  
      if (cls.keyCatchers == 0)
      {   // FIXME: KEYCATCH_NONE
        if (repeated_press(&event) == qtrue)
          continue;
      } // if
      XLateKey(&event.xkey, &key);

      Sys_QueEvent( t, SE_KEY, key, qfalse, 0, NULL );
      break;

    case MotionNotify:
			t = Sys_XTimeToSysTime(event.xkey.time);
      if (mouse_active)
      {
        if (in_dgamouse->value)
        {
          if (abs(event.xmotion.x_root) > 1)
            mx += event.xmotion.x_root * 2;
          else
            mx += event.xmotion.x_root;
          if (abs(event.xmotion.y_root) > 1)
            my += event.xmotion.y_root * 2;
          else
            my += event.xmotion.y_root;
          if (t - mouseResetTime > MOUSE_RESET_DELAY )
          {
            Sys_QueEvent( t, SE_MOUSE, mx, my, 0, NULL );
          }
          mx = my = 0;
        } else
        {
          // If it's a center motion, we've just returned from our warp
          if (event.xmotion.x == glConfig.vidWidth/2 &&
              event.xmotion.y == glConfig.vidHeight/2)
          {
            mwx = glConfig.vidWidth/2;
            mwy = glConfig.vidHeight/2;
            if (t - mouseResetTime > MOUSE_RESET_DELAY )
            {
              Sys_QueEvent( t, SE_MOUSE, mx, my, 0, NULL );
            }
            mx = my = 0;
            break;
          }

          dx = ((int)event.xmotion.x - mwx);
          dy = ((int)event.xmotion.y - mwy);
          if (abs(dx) > 1)
            mx += dx * 2;
          else
            mx += dx;
          if (abs(dy) > 1)
            my += dy * 2;
          else
            my += dy;

          mwx = event.xmotion.x;
          mwy = event.xmotion.y;
          dowarp = qtrue;
        }
      }
      break;

    case ButtonPress:
		  t = Sys_XTimeToSysTime(event.xkey.time);
      if (event.xbutton.button == 4)
      {
        Sys_QueEvent( t, SE_KEY, K_MWHEELUP, qtrue, 0, NULL );
      } else if (event.xbutton.button == 5)
      {
        Sys_QueEvent( t, SE_KEY, K_MWHEELDOWN, qtrue, 0, NULL );
      } else
      {
        // NOTE TTimo there seems to be a weird mapping for K_MOUSE1 K_MOUSE2 K_MOUSE3 ..
        b=-1;
        if (event.xbutton.button == 1)
        {
          b = 0; // K_MOUSE1
        } else if (event.xbutton.button == 2)
        {
          b = 2; // K_MOUSE3
        } else if (event.xbutton.button == 3)
        {
          b = 1; // K_MOUSE2
        } else if (event.xbutton.button == 6)
        {
          b = 3; // K_MOUSE4
        } else if (event.xbutton.button == 7)
        {
          b = 4; // K_MOUSE5
        };

        Sys_QueEvent( t, SE_KEY, K_MOUSE1 + b, qtrue, 0, NULL );
      }
      break;

    case ButtonRelease:
		  t = Sys_XTimeToSysTime(event.xkey.time);
      if (event.xbutton.button == 4)
      {
        Sys_QueEvent( t, SE_KEY, K_MWHEELUP, qfalse, 0, NULL );
      } else if (event.xbutton.button == 5)
      {
        Sys_QueEvent( t, SE_KEY, K_MWHEELDOWN, qfalse, 0, NULL );
      } else
      {
        b=-1;
        if (event.xbutton.button == 1)
        {
          b = 0;
        } else if (event.xbutton.button == 2)
        {
          b = 2;
        } else if (event.xbutton.button == 3)
        {
          b = 1;
        } else if (event.xbutton.button == 6)
        {
          b = 3; // K_MOUSE4
        } else if (event.xbutton.button == 7)
        {
          b = 4; // K_MOUSE5
        };
        Sys_QueEvent( t, SE_KEY, K_MOUSE1 + b, qfalse, 0, NULL );
      }
      break;

    case CreateNotify :
      win_x = event.xcreatewindow.x;
      win_y = event.xcreatewindow.y;
      break;

    case ConfigureNotify :
      win_x = event.xconfigure.x;
      win_y = event.xconfigure.y;
      break;
    }
  }

  if (dowarp)
  {
    XWarpPointer(dpy,None,win,0,0,0,0, 
                 (glConfig.vidWidth/2),(glConfig.vidHeight/2));
  }
}