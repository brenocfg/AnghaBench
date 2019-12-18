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
typedef  int /*<<< orphan*/  XKeyEvent ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int) ;} ;
typedef  int KeySym ;

/* Variables and functions */
 int K_ALT ; 
 int K_BACKSPACE ; 
 int K_CTRL ; 
 int K_DEL ; 
 int K_DOWNARROW ; 
 int K_END ; 
 int K_ENTER ; 
 int K_ESCAPE ; 
 int K_F1 ; 
 int K_F10 ; 
 int K_F11 ; 
 int K_F12 ; 
 int K_F2 ; 
 int K_F3 ; 
 int K_F4 ; 
 int K_F5 ; 
 int K_F6 ; 
 int K_F7 ; 
 int K_F8 ; 
 int K_F9 ; 
 int K_HOME ; 
 int K_INS ; 
 int K_KP_5 ; 
 int K_KP_DEL ; 
 int K_KP_DOWNARROW ; 
 int K_KP_END ; 
 int K_KP_ENTER ; 
 int K_KP_HOME ; 
 int K_KP_INS ; 
 int K_KP_LEFTARROW ; 
 int K_KP_MINUS ; 
 int K_KP_PGDN ; 
 int K_KP_PGUP ; 
 int K_KP_PLUS ; 
 int K_KP_RIGHTARROW ; 
 int K_KP_SLASH ; 
 int K_KP_UPARROW ; 
 int K_LEFTARROW ; 
 int K_PAUSE ; 
 int K_PGDN ; 
 int K_PGUP ; 
 int K_RIGHTARROW ; 
 int K_SHIFT ; 
 int K_SPACE ; 
 int K_TAB ; 
 int K_UPARROW ; 
 int /*<<< orphan*/  PRINT_ALL ; 
#define  XK_Alt_L 202 
#define  XK_Alt_R 201 
#define  XK_BackSpace 200 
#define  XK_Control_L 199 
#define  XK_Control_R 198 
#define  XK_Delete 197 
#define  XK_Down 196 
#define  XK_End 195 
#define  XK_Escape 194 
#define  XK_Execute 193 
#define  XK_F1 192 
#define  XK_F10 191 
#define  XK_F11 190 
#define  XK_F12 189 
#define  XK_F2 188 
#define  XK_F3 187 
#define  XK_F4 186 
#define  XK_F5 185 
#define  XK_F6 184 
#define  XK_F7 183 
#define  XK_F8 182 
#define  XK_F9 181 
#define  XK_Home 180 
#define  XK_Insert 179 
#define  XK_KP_0 178 
#define  XK_KP_1 177 
#define  XK_KP_2 176 
#define  XK_KP_3 175 
#define  XK_KP_4 174 
#define  XK_KP_6 173 
#define  XK_KP_7 172 
#define  XK_KP_8 171 
#define  XK_KP_9 170 
#define  XK_KP_Add 169 
#define  XK_KP_Begin 168 
#define  XK_KP_Decimal 167 
#define  XK_KP_Delete 166 
#define  XK_KP_Divide 165 
#define  XK_KP_Down 164 
#define  XK_KP_End 163 
#define  XK_KP_Enter 162 
#define  XK_KP_Home 161 
#define  XK_KP_Insert 160 
#define  XK_KP_Left 159 
#define  XK_KP_Multiply 158 
#define  XK_KP_Page_Down 157 
#define  XK_KP_Page_Up 156 
#define  XK_KP_Right 155 
#define  XK_KP_Space 154 
#define  XK_KP_Subtract 153 
#define  XK_KP_Up 152 
#define  XK_Left 151 
#define  XK_Meta_L 150 
#define  XK_Meta_R 149 
#define  XK_Page_Down 148 
#define  XK_Page_Up 147 
#define  XK_Pause 146 
#define  XK_Return 145 
#define  XK_Right 144 
#define  XK_Shift_L 143 
#define  XK_Shift_R 142 
#define  XK_Tab 141 
#define  XK_Up 140 
#define  XK_ampersand 139 
#define  XK_asciicircum 138 
#define  XK_asterisk 137 
#define  XK_at 136 
#define  XK_dollar 135 
#define  XK_exclam 134 
#define  XK_numbersign 133 
#define  XK_parenleft 132 
#define  XK_parenright 131 
#define  XK_percent 130 
#define  XK_space 129 
#define  XK_twosuperior 128 
 int XLookupString (int /*<<< orphan*/ *,char*,int,int*,int /*<<< orphan*/ ) ; 
 TYPE_2__* com_developer ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *XLateKey(XKeyEvent *ev, int *key)
{
  static char buf[64];
  KeySym keysym;
  int XLookupRet;

  *key = 0;

  XLookupRet = XLookupString(ev, buf, sizeof buf, &keysym, 0);
#ifdef KBD_DBG
  ri.Printf(PRINT_ALL, "XLookupString ret: %d buf: %s keysym: %x\n", XLookupRet, buf, keysym);
#endif
  
  switch (keysym)
  {
  case XK_KP_Page_Up: 
  case XK_KP_9:  *key = K_KP_PGUP; break;
  case XK_Page_Up:   *key = K_PGUP; break;

  case XK_KP_Page_Down: 
  case XK_KP_3: *key = K_KP_PGDN; break;
  case XK_Page_Down:   *key = K_PGDN; break;

  case XK_KP_Home: *key = K_KP_HOME; break;
  case XK_KP_7: *key = K_KP_HOME; break;
  case XK_Home:  *key = K_HOME; break;

  case XK_KP_End:
  case XK_KP_1:   *key = K_KP_END; break;
  case XK_End:   *key = K_END; break;

  case XK_KP_Left: *key = K_KP_LEFTARROW; break;
  case XK_KP_4: *key = K_KP_LEFTARROW; break;
  case XK_Left:  *key = K_LEFTARROW; break;

  case XK_KP_Right: *key = K_KP_RIGHTARROW; break;
  case XK_KP_6: *key = K_KP_RIGHTARROW; break;
  case XK_Right:  *key = K_RIGHTARROW;    break;

  case XK_KP_Down:
  case XK_KP_2:    *key = K_KP_DOWNARROW; break;
  case XK_Down:  *key = K_DOWNARROW; break;

  case XK_KP_Up:   
  case XK_KP_8:    *key = K_KP_UPARROW; break;
  case XK_Up:    *key = K_UPARROW;   break;

  case XK_Escape: *key = K_ESCAPE;    break;

  case XK_KP_Enter: *key = K_KP_ENTER;  break;
  case XK_Return: *key = K_ENTER;    break;

  case XK_Tab:    *key = K_TAB;      break;

  case XK_F1:    *key = K_F1;       break;

  case XK_F2:    *key = K_F2;       break;

  case XK_F3:    *key = K_F3;       break;

  case XK_F4:    *key = K_F4;       break;

  case XK_F5:    *key = K_F5;       break;

  case XK_F6:    *key = K_F6;       break;

  case XK_F7:    *key = K_F7;       break;

  case XK_F8:    *key = K_F8;       break;

  case XK_F9:    *key = K_F9;       break;

  case XK_F10:    *key = K_F10;      break;

  case XK_F11:    *key = K_F11;      break;

  case XK_F12:    *key = K_F12;      break;

    // bk001206 - from Ryan's Fakk2 
    //case XK_BackSpace: *key = 8; break; // ctrl-h
  case XK_BackSpace: *key = K_BACKSPACE; break; // ctrl-h

  case XK_KP_Delete:
  case XK_KP_Decimal: *key = K_KP_DEL; break;
  case XK_Delete: *key = K_DEL; break;

  case XK_Pause:  *key = K_PAUSE;    break;

  case XK_Shift_L:
  case XK_Shift_R:  *key = K_SHIFT;   break;

  case XK_Execute: 
  case XK_Control_L: 
  case XK_Control_R:  *key = K_CTRL;  break;

  case XK_Alt_L:  
  case XK_Meta_L: 
  case XK_Alt_R:  
  case XK_Meta_R: *key = K_ALT;     break;

  case XK_KP_Begin: *key = K_KP_5;  break;

  case XK_Insert:   *key = K_INS; break;
  case XK_KP_Insert:
  case XK_KP_0: *key = K_KP_INS; break;

  case XK_KP_Multiply: *key = '*'; break;
  case XK_KP_Add:  *key = K_KP_PLUS; break;
  case XK_KP_Subtract: *key = K_KP_MINUS; break;
  case XK_KP_Divide: *key = K_KP_SLASH; break;

    // bk001130 - from cvs1.17 (mkv)
  case XK_exclam: *key = '1'; break;
  case XK_at: *key = '2'; break;
  case XK_numbersign: *key = '3'; break;
  case XK_dollar: *key = '4'; break;
  case XK_percent: *key = '5'; break;
  case XK_asciicircum: *key = '6'; break;
  case XK_ampersand: *key = '7'; break;
  case XK_asterisk: *key = '8'; break;
  case XK_parenleft: *key = '9'; break;
  case XK_parenright: *key = '0'; break;
  
  // weird french keyboards ..
  // NOTE: console toggle is hardcoded in cl_keys.c, can't be unbound
  //   cleaner would be .. using hardware key codes instead of the key syms
  //   could also add a new K_KP_CONSOLE
  case XK_twosuperior: *key = '~'; break;
		
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=472
	case XK_space:
	case XK_KP_Space: *key = K_SPACE; break;

  default:
    if (XLookupRet == 0)
    {
      if (com_developer->value)
      {
        ri.Printf(PRINT_ALL, "Warning: XLookupString failed on KeySym %d\n", keysym);
      }
      return NULL;
    }
    else
    {
      // XK_* tests failed, but XLookupString got a buffer, so let's try it
      *key = *(unsigned char *)buf;
      if (*key >= 'A' && *key <= 'Z')
        *key = *key - 'A' + 'a';
      // if ctrl is pressed, the keys are not between 'A' and 'Z', for instance ctrl-z == 26 ^Z ^C etc.
      // see https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=19
      else if (*key >= 1 && *key <= 26)
     	  *key = *key + 'a' - 1;
    }
    break;
  } 

  return buf;
}