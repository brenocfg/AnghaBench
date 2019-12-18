#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int16_t ;
struct TYPE_4__ {int btns_h; } ;
typedef  TYPE_1__ WPADData ;

/* Variables and functions */
 int /*<<< orphan*/  BIT64_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT64_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int DEFAULT_MAX_PADS ; 
 int GX_CLASSIC_A ; 
 int GX_CLASSIC_B ; 
 int GX_CLASSIC_DOWN ; 
 int GX_CLASSIC_HOME ; 
 int GX_CLASSIC_LEFT ; 
 int GX_CLASSIC_L_TRIGGER ; 
 int GX_CLASSIC_MINUS ; 
 int GX_CLASSIC_PLUS ; 
 int GX_CLASSIC_RIGHT ; 
 int GX_CLASSIC_R_TRIGGER ; 
 int GX_CLASSIC_UP ; 
 int GX_CLASSIC_X ; 
 int GX_CLASSIC_Y ; 
 int GX_CLASSIC_ZL_TRIGGER ; 
 int GX_CLASSIC_ZR_TRIGGER ; 
 int GX_GC_A ; 
 int GX_GC_B ; 
 int GX_GC_DOWN ; 
 int GX_GC_HOME ; 
 int GX_GC_LEFT ; 
 int GX_GC_L_TRIGGER ; 
 int GX_GC_RIGHT ; 
 int GX_GC_R_TRIGGER ; 
 int GX_GC_START ; 
 int GX_GC_UP ; 
 int GX_GC_X ; 
 int GX_GC_Y ; 
 int GX_GC_Z_TRIGGER ; 
 int GX_NUNCHUK_C ; 
 int GX_NUNCHUK_Z ; 
 int GX_WIIMOTE_1 ; 
 int GX_WIIMOTE_2 ; 
 int GX_WIIMOTE_A ; 
 int GX_WIIMOTE_B ; 
 int GX_WIIMOTE_DOWN ; 
 int GX_WIIMOTE_HOME ; 
 int GX_WIIMOTE_LEFT ; 
 int GX_WIIMOTE_MINUS ; 
 int GX_WIIMOTE_PLUS ; 
 int GX_WIIMOTE_RIGHT ; 
 int GX_WIIMOTE_UP ; 
 int PAD_BUTTON_A ; 
 int PAD_BUTTON_B ; 
 int PAD_BUTTON_DOWN ; 
 int PAD_BUTTON_LEFT ; 
 int PAD_BUTTON_RIGHT ; 
 int PAD_BUTTON_START ; 
 int PAD_BUTTON_UP ; 
 int PAD_BUTTON_X ; 
 int PAD_BUTTON_Y ; 
 int PAD_ButtonsHeld (unsigned int) ; 
 int PAD_ScanPads () ; 
 scalar_t__ PAD_StickX (unsigned int) ; 
 scalar_t__ PAD_StickY (unsigned int) ; 
 scalar_t__ PAD_SubStickX (unsigned int) ; 
 scalar_t__ PAD_SubStickY (unsigned int) ; 
 int PAD_TRIGGER_L ; 
 int PAD_TRIGGER_R ; 
 int PAD_TRIGGER_Z ; 
 int PAD_TriggerL (unsigned int) ; 
 int PAD_TriggerR (unsigned int) ; 
 int /*<<< orphan*/  RARCH_CTL_SET_SHUTDOWN ; 
 int /*<<< orphan*/  RARCH_MENU_TOGGLE ; 
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_LEFT ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
 int UINT64_C (int) ; 
 scalar_t__ WPADProbe (unsigned int,int*) ; 
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
 unsigned int WPAD_CHAN_0 ; 
 unsigned int WPAD_CHAN_1 ; 
 int /*<<< orphan*/  WPAD_CHAN_ALL ; 
 int WPAD_CLASSIC_BUTTON_A ; 
 int WPAD_CLASSIC_BUTTON_B ; 
 int WPAD_CLASSIC_BUTTON_DOWN ; 
 int WPAD_CLASSIC_BUTTON_FULL_L ; 
 int WPAD_CLASSIC_BUTTON_FULL_R ; 
 int WPAD_CLASSIC_BUTTON_HOME ; 
 int WPAD_CLASSIC_BUTTON_LEFT ; 
 int WPAD_CLASSIC_BUTTON_MINUS ; 
 int WPAD_CLASSIC_BUTTON_PLUS ; 
 int WPAD_CLASSIC_BUTTON_RIGHT ; 
 int WPAD_CLASSIC_BUTTON_UP ; 
 int WPAD_CLASSIC_BUTTON_X ; 
 int WPAD_CLASSIC_BUTTON_Y ; 
 int WPAD_CLASSIC_BUTTON_ZL ; 
 int WPAD_CLASSIC_BUTTON_ZR ; 
 scalar_t__ WPAD_Data (unsigned int) ; 
 scalar_t__ WPAD_ERR_NONE ; 
 int WPAD_EXP_CLASSIC ; 
 int WPAD_EXP_GAMECUBE ; 
 int WPAD_EXP_NOCONTROLLER ; 
 int WPAD_EXP_NONE ; 
 int WPAD_EXP_NUNCHUK ; 
 int WPAD_NUNCHUK_BUTTON_C ; 
 int WPAD_NUNCHUK_BUTTON_Z ; 
 int /*<<< orphan*/  WPAD_ReadPending (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int WPAD_StickX (TYPE_1__*,int) ; 
 int WPAD_StickY (TYPE_1__*,int) ; 
 int*** analog_state ; 
 int /*<<< orphan*/  check_port0_active (int) ; 
 int g_menu ; 
 int g_quit ; 
 scalar_t__ gx_joypad_query_pad (unsigned int) ; 
 int /*<<< orphan*/  gx_mouse_info (int,unsigned int) ; 
 int /*<<< orphan*/  handle_hotplug (unsigned int,int) ; 
 int /*<<< orphan*/  lifecycle_state ; 
 int* pad_state ; 
 int* pad_type ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gx_joypad_poll(void)
{
   unsigned i, j, port;
   uint8_t pad_count = 0;
   uint8_t gcpad = 0;
   uint64_t state_p1;
   uint64_t check_menu_toggle;

   pad_state[0] = 0;
   pad_state[1] = 0;
   pad_state[2] = 0;
   pad_state[3] = 0;

   gcpad = PAD_ScanPads();

#ifdef HW_RVL
   if (g_quit)
   {
      rarch_ctl(RARCH_CTL_SET_SHUTDOWN, NULL);
      g_quit = false;
      return;
   }

   WPAD_ReadPending(WPAD_CHAN_ALL, NULL);
#endif

   for (port = 0; port < DEFAULT_MAX_PADS; port++)
   {
      uint32_t down = 0, ptype = WPAD_EXP_NOCONTROLLER;
      uint64_t *state_cur = &pad_state[port];

      if (gcpad & (1 << port))
      {
         int16_t ls_x, ls_y, rs_x, rs_y;
         uint64_t menu_combo = 0;

         down = PAD_ButtonsHeld(port);

         *state_cur |= (down & PAD_BUTTON_A) ? (UINT64_C(1) << GX_GC_A) : 0;
         *state_cur |= (down & PAD_BUTTON_B) ? (UINT64_C(1) << GX_GC_B) : 0;
         *state_cur |= (down & PAD_BUTTON_X) ? (UINT64_C(1) << GX_GC_X) : 0;
         *state_cur |= (down & PAD_BUTTON_Y) ? (UINT64_C(1) << GX_GC_Y) : 0;
         *state_cur |= (down & PAD_BUTTON_UP) ? (UINT64_C(1) << GX_GC_UP) : 0;
         *state_cur |= (down & PAD_BUTTON_DOWN) ? (UINT64_C(1) << GX_GC_DOWN) : 0;
         *state_cur |= (down & PAD_BUTTON_LEFT) ? (UINT64_C(1) << GX_GC_LEFT) : 0;
         *state_cur |= (down & PAD_BUTTON_RIGHT) ? (UINT64_C(1) << GX_GC_RIGHT) : 0;
         *state_cur |= (down & PAD_BUTTON_START) ? (UINT64_C(1) << GX_GC_START) : 0;
         *state_cur |= (down & PAD_TRIGGER_Z) ? (UINT64_C(1) << GX_GC_Z_TRIGGER) : 0;
         *state_cur |= ((down & PAD_TRIGGER_L) || PAD_TriggerL(port) > 127) ? (UINT64_C(1) << GX_GC_L_TRIGGER) : 0;
         *state_cur |= ((down & PAD_TRIGGER_R) || PAD_TriggerR(port) > 127) ? (UINT64_C(1) << GX_GC_R_TRIGGER) : 0;

         ls_x = (int16_t)PAD_StickX(port) * 256;
         ls_y = (int16_t)PAD_StickY(port) * -256;
         rs_x = (int16_t)PAD_SubStickX(port) * 256;
         rs_y = (int16_t)PAD_SubStickY(port) * -256;

         analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_X] = ls_x;
         analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_Y] = ls_y;
         analog_state[port][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_X] = rs_x;
         analog_state[port][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_Y] = rs_y;

         menu_combo = (UINT64_C(1) << GX_GC_START) | (UINT64_C(1) << GX_GC_Z_TRIGGER) |
                      (UINT64_C(1) << GX_GC_L_TRIGGER) | (UINT64_C(1) << GX_GC_R_TRIGGER);

         if ((*state_cur & menu_combo) == menu_combo)
            *state_cur |= (UINT64_C(1) << GX_GC_HOME);

         ptype = WPAD_EXP_GAMECUBE;
      }
#ifdef HW_RVL
      else if (WPADProbe(port, &ptype) == WPAD_ERR_NONE)
      {
         WPADData *wpaddata = (WPADData*)WPAD_Data(port);

         down = wpaddata->btns_h;

         /* Mouse & Lightgun: Retrieve IR data */
         if (ptype == WPAD_EXP_NONE)
            if (port == WPAD_CHAN_0 || port == WPAD_CHAN_1)
               gx_mouse_info(wpaddata->btns_h, port);

         *state_cur |= (down & WPAD_BUTTON_A) ? (UINT64_C(1) << GX_WIIMOTE_A) : 0;
         *state_cur |= (down & WPAD_BUTTON_B) ? (UINT64_C(1) << GX_WIIMOTE_B) : 0;
         *state_cur |= (down & WPAD_BUTTON_1) ? (UINT64_C(1) << GX_WIIMOTE_1) : 0;
         *state_cur |= (down & WPAD_BUTTON_2) ? (UINT64_C(1) << GX_WIIMOTE_2) : 0;
         *state_cur |= (down & WPAD_BUTTON_PLUS) ? (UINT64_C(1) << GX_WIIMOTE_PLUS) : 0;
         *state_cur |= (down & WPAD_BUTTON_MINUS) ? (UINT64_C(1) << GX_WIIMOTE_MINUS) : 0;
         *state_cur |= (down & WPAD_BUTTON_HOME) ? (UINT64_C(1) << GX_WIIMOTE_HOME) : 0;



         if (ptype != WPAD_EXP_NUNCHUK)
         {
            /* Rotated d-pad on Wiimote. */
            *state_cur |= (down & WPAD_BUTTON_UP) ? (UINT64_C(1) << GX_WIIMOTE_LEFT) : 0;
            *state_cur |= (down & WPAD_BUTTON_DOWN) ? (UINT64_C(1) << GX_WIIMOTE_RIGHT) : 0;
            *state_cur |= (down & WPAD_BUTTON_LEFT) ? (UINT64_C(1) << GX_WIIMOTE_DOWN) : 0;
            *state_cur |= (down & WPAD_BUTTON_RIGHT) ? (UINT64_C(1) << GX_WIIMOTE_UP) : 0;
         }

         if (ptype == WPAD_EXP_CLASSIC)
         {
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_A) ? (UINT64_C(1) << GX_CLASSIC_A) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_B) ? (UINT64_C(1) << GX_CLASSIC_B) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_X) ? (UINT64_C(1) << GX_CLASSIC_X) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_Y) ? (UINT64_C(1) << GX_CLASSIC_Y) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_UP) ? (UINT64_C(1) << GX_CLASSIC_UP) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_DOWN) ? (UINT64_C(1) << GX_CLASSIC_DOWN) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_LEFT) ? (UINT64_C(1) << GX_CLASSIC_LEFT) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_RIGHT) ? (UINT64_C(1) << GX_CLASSIC_RIGHT) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_PLUS) ? (UINT64_C(1) << GX_CLASSIC_PLUS) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_MINUS) ? (UINT64_C(1) << GX_CLASSIC_MINUS) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_HOME) ? (UINT64_C(1) << GX_CLASSIC_HOME) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_FULL_L) ? (UINT64_C(1) << GX_CLASSIC_L_TRIGGER) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_FULL_R) ? (UINT64_C(1) << GX_CLASSIC_R_TRIGGER) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_ZL) ? (UINT64_C(1) << GX_CLASSIC_ZL_TRIGGER) : 0;
            *state_cur |= (down & WPAD_CLASSIC_BUTTON_ZR) ? (UINT64_C(1) << GX_CLASSIC_ZR_TRIGGER) : 0;

            analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_X]  = WPAD_StickX(wpaddata, 0);
            analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_Y]  = WPAD_StickY(wpaddata, 0);
            analog_state[port][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_X] = WPAD_StickX(wpaddata, 1);
            analog_state[port][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_Y] = WPAD_StickY(wpaddata, 1);
         }
         else if (ptype == WPAD_EXP_NUNCHUK)
         {
            /* Wiimote is held upright with nunchuk,
             * do not change d-pad orientation. */
            *state_cur |= (down & WPAD_BUTTON_UP) ? (UINT64_C(1) << GX_WIIMOTE_UP) : 0;
            *state_cur |= (down & WPAD_BUTTON_DOWN) ? (UINT64_C(1) << GX_WIIMOTE_DOWN) : 0;
            *state_cur |= (down & WPAD_BUTTON_LEFT) ? (UINT64_C(1) << GX_WIIMOTE_LEFT) : 0;
            *state_cur |= (down & WPAD_BUTTON_RIGHT) ? (UINT64_C(1) << GX_WIIMOTE_RIGHT) : 0;

            *state_cur |= (down & WPAD_NUNCHUK_BUTTON_Z) ? (UINT64_C(1) << GX_NUNCHUK_Z) : 0;
            *state_cur |= (down & WPAD_NUNCHUK_BUTTON_C) ? (UINT64_C(1) << GX_NUNCHUK_C) : 0;

            analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_X] = WPAD_StickX(wpaddata, 0);
            analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_Y] = WPAD_StickY(wpaddata, 0);
         }
      }
#endif

      /* Count active controllers */
      if(gx_joypad_query_pad(port))
         pad_count++;

      /* Always enable 1 pad in port 0 if there's only 1 controller connected. 
       * This avoids being stuck in rgui input settings. */
      check_port0_active(pad_count);

      if (ptype != pad_type[port])
         handle_hotplug(port, ptype);

      for (i = 0; i < 2; i++)
         for (j = 0; j < 2; j++)
            if (analog_state[port][i][j] == -0x8000)
               analog_state[port][i][j] = -0x7fff;
   }

   state_p1 = pad_state[0];

   BIT64_CLEAR(lifecycle_state, RARCH_MENU_TOGGLE);
   if (g_menu)
   {
      state_p1 |= (UINT64_C(1) << GX_GC_HOME);
      g_menu = false;
   }

   check_menu_toggle = UINT64_C(1) << GX_GC_HOME;
#ifdef HW_RVL
   check_menu_toggle |= (UINT64_C(1) << GX_WIIMOTE_HOME) | (UINT64_C(1) << GX_CLASSIC_HOME);
#endif

   if (check_menu_toggle & state_p1)
      BIT64_SET(lifecycle_state, RARCH_MENU_TOGGLE);
}