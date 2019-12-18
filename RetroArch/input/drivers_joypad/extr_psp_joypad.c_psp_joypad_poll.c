#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ input_backtouch_toggle; scalar_t__ input_backtouch_enable; } ;
struct TYPE_22__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;
struct TYPE_27__ {scalar_t__* port; } ;
struct TYPE_26__ {int /*<<< orphan*/  ident; } ;
struct TYPE_25__ {scalar_t__* port; } ;
struct TYPE_24__ {int buttons; int Buttons; } ;
struct TYPE_23__ {unsigned int reportNum; TYPE_2__* report; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_4__ SceTouchData ;
typedef  int /*<<< orphan*/  SceCtrlPortInfo ;
typedef  TYPE_5__ SceCtrlData ;
typedef  int /*<<< orphan*/  SceCtrlActuator ;

/* Variables and functions */
 int /*<<< orphan*/  BIT64_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT64_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CtrlPeekBufferPositive (unsigned int,TYPE_5__*,int) ; 
 int /*<<< orphan*/  CtrlSetSamplingMode (int /*<<< orphan*/ ) ; 
 unsigned int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  DEFAULT_SAMPLING_MODE ; 
 int LERP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NE_AREA (int,int) ; 
 scalar_t__ NW_AREA (int,int) ; 
 int PSP_CTRL_CIRCLE ; 
 int PSP_CTRL_CROSS ; 
 int PSP_CTRL_DOWN ; 
 int PSP_CTRL_L ; 
 int PSP_CTRL_L2 ; 
 int PSP_CTRL_L3 ; 
 int PSP_CTRL_LEFT ; 
 int PSP_CTRL_NOTE ; 
 int PSP_CTRL_R ; 
 int PSP_CTRL_R2 ; 
 int PSP_CTRL_R3 ; 
 int PSP_CTRL_RIGHT ; 
 int PSP_CTRL_SELECT ; 
 int PSP_CTRL_SQUARE ; 
 int PSP_CTRL_START ; 
 int PSP_CTRL_TRIANGLE ; 
 int PSP_CTRL_UP ; 
 int /*<<< orphan*/  RARCH_MENU_TOGGLE ; 
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 int RETRO_DEVICE_ID_JOYPAD_A ; 
 int RETRO_DEVICE_ID_JOYPAD_B ; 
 int RETRO_DEVICE_ID_JOYPAD_DOWN ; 
 int RETRO_DEVICE_ID_JOYPAD_L ; 
 int RETRO_DEVICE_ID_JOYPAD_L2 ; 
 int RETRO_DEVICE_ID_JOYPAD_L3 ; 
 int RETRO_DEVICE_ID_JOYPAD_LEFT ; 
 int RETRO_DEVICE_ID_JOYPAD_R ; 
 int RETRO_DEVICE_ID_JOYPAD_R2 ; 
 int RETRO_DEVICE_ID_JOYPAD_R3 ; 
 int RETRO_DEVICE_ID_JOYPAD_RIGHT ; 
 int RETRO_DEVICE_ID_JOYPAD_SELECT ; 
 int RETRO_DEVICE_ID_JOYPAD_START ; 
 int RETRO_DEVICE_ID_JOYPAD_UP ; 
 int RETRO_DEVICE_ID_JOYPAD_X ; 
 int RETRO_DEVICE_ID_JOYPAD_Y ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_LEFT ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
 scalar_t__ SCE_CTRL_TYPE_UNPAIRED ; 
 scalar_t__ SCE_KERNEL_MODEL_VITA ; 
 scalar_t__ SCE_KERNEL_MODEL_VITATV ; 
 int /*<<< orphan*/  SCE_TOUCH_PORT_BACK ; 
 int /*<<< orphan*/  SCE_TOUCH_PORT_FRONT ; 
 int /*<<< orphan*/  SCREEN_HEIGHT ; 
 int /*<<< orphan*/  SCREEN_WIDTH ; 
 scalar_t__ SE_AREA (int,int) ; 
 int STATE_ANALOGLX (TYPE_5__) ; 
 int STATE_ANALOGLY (TYPE_5__) ; 
 int STATE_ANALOGRX (TYPE_5__) ; 
 int STATE_ANALOGRY (TYPE_5__) ; 
 int STATE_BUTTON (TYPE_5__) ; 
 scalar_t__ SW_AREA (int,int) ; 
 int /*<<< orphan*/  TOUCH_MAX_HEIGHT ; 
 int /*<<< orphan*/  TOUCH_MAX_WIDTH ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/ * actuators ; 
 int*** analog_state ; 
 TYPE_3__* config_get_ptr () ; 
 TYPE_7__ curr_ctrl_info ; 
 int /*<<< orphan*/  input_autoconfigure_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lifecycle_state ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_9__ old_ctrl_info ; 
 int* pad_state ; 
 scalar_t__ psp2_model ; 
 TYPE_8__ psp_joypad ; 
 int /*<<< orphan*/  psp_joypad_name (unsigned int) ; 
 int read_system_buttons () ; 
 int /*<<< orphan*/  sceCtrlGetControllerPortInfo (TYPE_7__*) ; 
 int /*<<< orphan*/  sceCtrlSetSamplingCycle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceTouchPeek (int /*<<< orphan*/ ,TYPE_4__*,int) ; 

__attribute__((used)) static void psp_joypad_poll(void)
{
   unsigned player;
   unsigned players_count = DEFAULT_MAX_PADS;
#if defined(VITA)
   settings_t *settings = config_get_ptr();
#endif

#ifdef PSP
   sceCtrlSetSamplingCycle(0);
#endif

#ifdef VITA
   if (psp2_model != SCE_KERNEL_MODEL_VITATV)
      players_count = 1;
   else
   {
      sceCtrlGetControllerPortInfo(&curr_ctrl_info);
      for (player = 0; player < players_count; player++)
      {
         if (old_ctrl_info.port[player + 1] == curr_ctrl_info.port[player + 1])
            continue;

         if (old_ctrl_info.port[player + 1] != SCE_CTRL_TYPE_UNPAIRED &&
               curr_ctrl_info.port[player + 1] == SCE_CTRL_TYPE_UNPAIRED)
         {
            memset(&actuators[player], 0, sizeof(SceCtrlActuator));
            input_autoconfigure_disconnect(player, psp_joypad.ident);
         }

         if (old_ctrl_info.port[player + 1] == SCE_CTRL_TYPE_UNPAIRED &&
               curr_ctrl_info.port[player + 1] != SCE_CTRL_TYPE_UNPAIRED)
            input_autoconfigure_connect(
                  psp_joypad_name(player),
                  NULL,
                  psp_joypad.ident,
                  player,
                  0,
                  0
                  );
      }
      memcpy(&old_ctrl_info, &curr_ctrl_info, sizeof(SceCtrlPortInfo));
   }
#endif

   CtrlSetSamplingMode(DEFAULT_SAMPLING_MODE);

   BIT64_CLEAR(lifecycle_state, RARCH_MENU_TOGGLE);

   for (player = 0; player < players_count; player++)
   {
      unsigned j, k;
      SceCtrlData state_tmp;
      unsigned i  = player;
#if defined(VITA)
      unsigned p = (psp2_model == SCE_KERNEL_MODEL_VITATV) ? player + 1 : player;
      if (curr_ctrl_info.port[p] == SCE_CTRL_TYPE_UNPAIRED)
         continue;
#elif defined(SN_TARGET_PSP2)
      /* Dumb hack, but here's the explanation -
       * sceCtrlPeekBufferPositive's port parameter
       * can be 0 or 1 to read the first controller on
       * a PSTV, but HAS to be 0 for a real VITA and 2
       * for the 2nd controller on a PSTV */
      unsigned p  = (player > 0) ? player+1 : player;
#else
      unsigned p  = player;
#endif
      int32_t ret = CtrlPeekBufferPositive(p, &state_tmp, 1);

      pad_state[i] = 0;
      analog_state[i][0][0] = analog_state[i][0][1] =
         analog_state[i][1][0] = analog_state[i][1][1] = 0;

#if defined(SN_TARGET_PSP2) || defined(VITA)
      if (ret < 0)
         continue;
#endif
#if defined(VITA)
      if (psp2_model == SCE_KERNEL_MODEL_VITA
         && settings->bools.input_backtouch_enable)
      {
         unsigned i;
         SceTouchData touch_surface = {0};
         sceTouchPeek(settings->bools.input_backtouch_toggle
               ? SCE_TOUCH_PORT_FRONT : SCE_TOUCH_PORT_BACK, &touch_surface, 1);

         for (i = 0; i < touch_surface.reportNum; i++)
         {
            int x = LERP(touch_surface.report[i].x, TOUCH_MAX_WIDTH, SCREEN_WIDTH);
            int y = LERP(touch_surface.report[i].y, TOUCH_MAX_HEIGHT, SCREEN_HEIGHT);
            if (NW_AREA(x, y)) state_tmp.buttons |= PSP_CTRL_L2;
            if (NE_AREA(x, y)) state_tmp.buttons |= PSP_CTRL_R2;
            if (SW_AREA(x, y)) state_tmp.buttons |= PSP_CTRL_L3;
            if (SE_AREA(x, y)) state_tmp.buttons |= PSP_CTRL_R3;
         }
      }
#endif
#ifdef HAVE_KERNEL_PRX
      state_tmp.Buttons = (state_tmp.Buttons & 0x0000FFFF)
         | (read_system_buttons() & 0xFFFF0000);
#endif

      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_LEFT) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_LEFT) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_DOWN) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_DOWN) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_RIGHT) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_RIGHT) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_UP) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_UP) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_START) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_START) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_SELECT) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_SELECT) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_TRIANGLE) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_X) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_SQUARE) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_Y) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_CROSS) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_B) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_CIRCLE) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_A) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_R) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_R) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_L) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_L) : 0;
#if defined(VITA)
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_R2) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_R2) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_L2) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_L2) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_R3) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_R3) : 0;
      pad_state[i] |= (STATE_BUTTON(state_tmp) & PSP_CTRL_L3) ? (UINT64_C(1) << RETRO_DEVICE_ID_JOYPAD_L3) : 0;
#endif

      analog_state[i][RETRO_DEVICE_INDEX_ANALOG_LEFT] [RETRO_DEVICE_ID_ANALOG_X] = (int16_t)(STATE_ANALOGLX(state_tmp)-128) * 256;
      analog_state[i][RETRO_DEVICE_INDEX_ANALOG_LEFT] [RETRO_DEVICE_ID_ANALOG_Y] = (int16_t)(STATE_ANALOGLY(state_tmp)-128) * 256;
#if defined(SN_TARGET_PSP2) || defined(VITA)
      analog_state[i][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_X] = (int16_t)(STATE_ANALOGRX(state_tmp)-128) * 256;
      analog_state[i][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_Y] = (int16_t)(STATE_ANALOGRY(state_tmp)-128) * 256;
#endif

#ifdef HAVE_KERNEL_PRX
      if (STATE_BUTTON(state_tmp) & PSP_CTRL_NOTE)
         BIT64_SET(lifecycle_state, RARCH_MENU_TOGGLE);
#endif

      for (j = 0; j < 2; j++)
         for (k = 0; k < 2; k++)
            if (analog_state[i][j][k] == -0x8000)
               analog_state[i][j][k] = -0x7fff;
   }
}