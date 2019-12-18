#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  keycode; } ;
struct TYPE_4__ {TYPE_1__ xkey; } ;

/* Variables and functions */
 int KEY_BACKSPACE ; 
 int KEY_DOWNARROW ; 
 int KEY_ENTER ; 
 int KEY_EQUALS ; 
 int KEY_ESCAPE ; 
 int KEY_F1 ; 
 int KEY_F10 ; 
 int KEY_F11 ; 
 int KEY_F12 ; 
 int KEY_F2 ; 
 int KEY_F3 ; 
 int KEY_F4 ; 
 int KEY_F5 ; 
 int KEY_F6 ; 
 int KEY_F7 ; 
 int KEY_F8 ; 
 int KEY_F9 ; 
 int KEY_LEFTARROW ; 
 int KEY_MINUS ; 
 int KEY_PAUSE ; 
 int KEY_RALT ; 
 int KEY_RCTRL ; 
 int KEY_RIGHTARROW ; 
 int KEY_RSHIFT ; 
 int KEY_TAB ; 
 int KEY_UPARROW ; 
#define  XK_Alt_L 161 
#define  XK_Alt_R 160 
#define  XK_BackSpace 159 
#define  XK_Control_L 158 
#define  XK_Control_R 157 
#define  XK_Delete 156 
#define  XK_Down 155 
#define  XK_Escape 154 
#define  XK_F1 153 
#define  XK_F10 152 
#define  XK_F11 151 
#define  XK_F12 150 
#define  XK_F2 149 
#define  XK_F3 148 
#define  XK_F4 147 
#define  XK_F5 146 
#define  XK_F6 145 
#define  XK_F7 144 
#define  XK_F8 143 
#define  XK_F9 142 
#define  XK_KP_Equal 141 
#define  XK_KP_Subtract 140 
#define  XK_Left 139 
#define  XK_Meta_L 138 
#define  XK_Meta_R 137 
#define  XK_Pause 136 
#define  XK_Return 135 
#define  XK_Right 134 
#define  XK_Shift_L 133 
#define  XK_Shift_R 132 
#define  XK_Tab 131 
#define  XK_Up 130 
 int XK_asciitilde ; 
#define  XK_equal 129 
#define  XK_minus 128 
 int XK_space ; 
 int XKeycodeToKeysym (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_display ; 
 TYPE_2__ X_event ; 

int xlatekey(void)
{

    int rc;

    switch(rc = XKeycodeToKeysym(X_display, X_event.xkey.keycode, 0))
    {
      case XK_Left:	rc = KEY_LEFTARROW;	break;
      case XK_Right:	rc = KEY_RIGHTARROW;	break;
      case XK_Down:	rc = KEY_DOWNARROW;	break;
      case XK_Up:	rc = KEY_UPARROW;	break;
      case XK_Escape:	rc = KEY_ESCAPE;	break;
      case XK_Return:	rc = KEY_ENTER;		break;
      case XK_Tab:	rc = KEY_TAB;		break;
      case XK_F1:	rc = KEY_F1;		break;
      case XK_F2:	rc = KEY_F2;		break;
      case XK_F3:	rc = KEY_F3;		break;
      case XK_F4:	rc = KEY_F4;		break;
      case XK_F5:	rc = KEY_F5;		break;
      case XK_F6:	rc = KEY_F6;		break;
      case XK_F7:	rc = KEY_F7;		break;
      case XK_F8:	rc = KEY_F8;		break;
      case XK_F9:	rc = KEY_F9;		break;
      case XK_F10:	rc = KEY_F10;		break;
      case XK_F11:	rc = KEY_F11;		break;
      case XK_F12:	rc = KEY_F12;		break;
	
      case XK_BackSpace:
      case XK_Delete:	rc = KEY_BACKSPACE;	break;

      case XK_Pause:	rc = KEY_PAUSE;		break;

      case XK_KP_Equal:
      case XK_equal:	rc = KEY_EQUALS;	break;

      case XK_KP_Subtract:
      case XK_minus:	rc = KEY_MINUS;		break;

      case XK_Shift_L:
      case XK_Shift_R:
	rc = KEY_RSHIFT;
	break;
	
      case XK_Control_L:
      case XK_Control_R:
	rc = KEY_RCTRL;
	break;
	
      case XK_Alt_L:
      case XK_Meta_L:
      case XK_Alt_R:
      case XK_Meta_R:
	rc = KEY_RALT;
	break;
	
      default:
	if (rc >= XK_space && rc <= XK_asciitilde)
	    rc = rc - XK_space + ' ';
	if (rc >= 'A' && rc <= 'Z')
	    rc = rc - 'A' + 'a';
	break;
    }

    return rc;

}