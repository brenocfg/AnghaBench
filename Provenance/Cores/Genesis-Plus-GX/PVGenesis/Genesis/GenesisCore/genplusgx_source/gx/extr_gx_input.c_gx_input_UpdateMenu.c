#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s16 ;
struct TYPE_7__ {int btns_d; int btns_h; } ;
typedef  TYPE_1__ WPADData ;
struct TYPE_9__ {scalar_t__ valid; } ;
struct TYPE_8__ {int keys; TYPE_5__ ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANALOG_SENSITIVITY ; 
 scalar_t__ HELD_DELAY ; 
 scalar_t__ HELD_SPEED ; 
 int PAD_BUTTONS_HELD ; 
 int PAD_BUTTON_A ; 
 int PAD_BUTTON_B ; 
 int PAD_BUTTON_DOWN ; 
 int PAD_BUTTON_LEFT ; 
 int PAD_BUTTON_RIGHT ; 
 int PAD_BUTTON_UP ; 
 int PAD_ButtonsDown (int /*<<< orphan*/ ) ; 
 int PAD_ButtonsHeld (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAD_ScanPads () ; 
 int /*<<< orphan*/  PAD_StickX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAD_StickY (int /*<<< orphan*/ ) ; 
 int PAD_TRIGGER_L ; 
 int PAD_TRIGGER_R ; 
 int PAD_TRIGGER_Z ; 
 int WPAD_BUTTONS_HELD ; 
 int WPAD_BUTTON_1 ; 
 int WPAD_BUTTON_2 ; 
 int WPAD_BUTTON_A ; 
 int WPAD_BUTTON_B ; 
 int WPAD_BUTTON_DOWN ; 
 int WPAD_BUTTON_HOME ; 
 int WPAD_BUTTON_LEFT ; 
 int WPAD_BUTTON_MINUS ; 
 int WPAD_BUTTON_PLUS ; 
 int WPAD_BUTTON_RIGHT ; 
 int WPAD_BUTTON_UP ; 
 int WPAD_CLASSIC_BUTTON_A ; 
 int WPAD_CLASSIC_BUTTON_B ; 
 int WPAD_CLASSIC_BUTTON_DOWN ; 
 int WPAD_CLASSIC_BUTTON_FULL_L ; 
 int WPAD_CLASSIC_BUTTON_FULL_R ; 
 int WPAD_CLASSIC_BUTTON_HOME ; 
 int WPAD_CLASSIC_BUTTON_LEFT ; 
 int WPAD_CLASSIC_BUTTON_RIGHT ; 
 int WPAD_CLASSIC_BUTTON_UP ; 
 TYPE_1__* WPAD_Data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPAD_IR (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  WPAD_ScanPads () ; 
 scalar_t__ held_cnt ; 
 scalar_t__ inputs_disabled ; 
 TYPE_4__ m_input ; 
 int /*<<< orphan*/  wpad_StickX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpad_StickY (TYPE_1__*,int /*<<< orphan*/ ) ; 

void gx_input_UpdateMenu(void)
{
  /* Check if inputs update are disabled */
  if (inputs_disabled) return;

  /* PAD status update */
  PAD_ScanPads();

  /* PAD pressed keys */
  s16 pp = PAD_ButtonsDown(0);

  /* PAD held keys (direction/selection) */
  s16 hp = PAD_ButtonsHeld(0) & PAD_BUTTONS_HELD;

  /* PAD analog sticks (handled as PAD held direction keys) */
  s8 x  = PAD_StickX(0);
  s8 y  = PAD_StickY(0);
  if (x > ANALOG_SENSITIVITY)       hp |= PAD_BUTTON_RIGHT;
  else if (x < -ANALOG_SENSITIVITY) hp |= PAD_BUTTON_LEFT;
  else if (y > ANALOG_SENSITIVITY)  hp |= PAD_BUTTON_UP;
  else if (y < -ANALOG_SENSITIVITY) hp |= PAD_BUTTON_DOWN;

#ifdef HW_RVL
  /* WPAD status update */
  WPAD_ScanPads();
  WPADData *data = WPAD_Data(0);

  /* WPAD pressed keys */
  u32 pw = data->btns_d;

  /* WPAD held keys (direction/selection) */
  u32 hw = data->btns_h & WPAD_BUTTONS_HELD;

  /* WPAD analog sticks (handled as PAD held direction keys) */
  x = wpad_StickX(data, 0);
  y = wpad_StickY(data, 0);
  if (x > ANALOG_SENSITIVITY)       hp |= PAD_BUTTON_RIGHT;
  else if (x < -ANALOG_SENSITIVITY) hp |= PAD_BUTTON_LEFT;
  else if (y > ANALOG_SENSITIVITY)  hp |= PAD_BUTTON_UP;
  else if (y < -ANALOG_SENSITIVITY) hp |= PAD_BUTTON_DOWN;
#endif

  /* check if any direction/selection key is being held or just being pressed/released */
#ifdef HW_RVL
  if (pp||pw) held_cnt = 0;
  else if (hp||hw) held_cnt++;
  else held_cnt = 0;
#else
  if (pp) held_cnt = 0;
  else if (hp) held_cnt++;
  else held_cnt = 0;
#endif

  /* initial delay (prevents triggering to start immediately) */
  if (held_cnt > HELD_DELAY)
  {
    /* key triggering */
    pp |= hp;
#ifdef HW_RVL
    pw |= hw;
#endif

    /* delay until next triggering (adjusts direction/selection update speed) */
    held_cnt -= HELD_SPEED;
  }

#ifdef HW_RVL
  /* Wiimote direction keys */
  WPAD_IR(0, &m_input.ir);
  if (m_input.ir.valid)
  {
    /* Wiimote is handled vertically */
    if (pw & WPAD_BUTTON_UP)         pp |= PAD_BUTTON_UP;
    else if (pw & WPAD_BUTTON_DOWN)  pp |= PAD_BUTTON_DOWN;
    else if (pw & WPAD_BUTTON_LEFT)  pp |= PAD_BUTTON_LEFT;
    else if (pw & WPAD_BUTTON_RIGHT) pp |= PAD_BUTTON_RIGHT;
  }
  else
  {
    /* Wiimote is handled horizontally */
    if (pw & WPAD_BUTTON_UP)         pp |= PAD_BUTTON_LEFT;
    else if (pw & WPAD_BUTTON_DOWN)  pp |= PAD_BUTTON_RIGHT;
    else if (pw & WPAD_BUTTON_LEFT)  pp |= PAD_BUTTON_DOWN;
    else if (pw & WPAD_BUTTON_RIGHT) pp |= PAD_BUTTON_UP;
  }

  /* Classic Controller direction keys */
  if (pw & WPAD_CLASSIC_BUTTON_UP)          pp |= PAD_BUTTON_UP;
  else if (pw & WPAD_CLASSIC_BUTTON_DOWN)   pp |= PAD_BUTTON_DOWN;
  else if (pw & WPAD_CLASSIC_BUTTON_LEFT)   pp |= PAD_BUTTON_LEFT;
  else if (pw & WPAD_CLASSIC_BUTTON_RIGHT)  pp |= PAD_BUTTON_RIGHT;

  /* WPAD buttons */
  if (pw & WPAD_BUTTON_A)               pp |= PAD_BUTTON_A;
  if (pw & WPAD_BUTTON_B)               pp |= PAD_BUTTON_B;
  if (pw & WPAD_BUTTON_2)               pp |= PAD_BUTTON_A;
  if (pw & WPAD_BUTTON_1)               pp |= PAD_BUTTON_B;
  if (pw & WPAD_BUTTON_HOME)            pp |= PAD_TRIGGER_Z;
  if (pw & WPAD_BUTTON_PLUS)            pp |= PAD_TRIGGER_L;
  if (pw & WPAD_BUTTON_MINUS)           pp |= PAD_TRIGGER_R;
  if (pw & WPAD_CLASSIC_BUTTON_FULL_L)  pp |= PAD_TRIGGER_L;
  if (pw & WPAD_CLASSIC_BUTTON_FULL_R)  pp |= PAD_TRIGGER_R;
  if (pw & WPAD_CLASSIC_BUTTON_A)       pp |= PAD_BUTTON_A;
  if (pw & WPAD_CLASSIC_BUTTON_B)       pp |= PAD_BUTTON_B;
  if (pw & WPAD_CLASSIC_BUTTON_HOME)    pp |= PAD_TRIGGER_Z;
#endif

  /* Update menu inputs */
  m_input.keys = pp;
}