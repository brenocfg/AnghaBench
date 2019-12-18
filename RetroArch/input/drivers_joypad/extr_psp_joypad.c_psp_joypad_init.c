#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ident; } ;
typedef  int /*<<< orphan*/  SceCtrlPortInfo ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 scalar_t__ SCE_KERNEL_MODEL_VITATV ; 
 int /*<<< orphan*/  SCE_TOUCH_PORT_BACK ; 
 int /*<<< orphan*/  SCE_TOUCH_PORT_FRONT ; 
 int /*<<< orphan*/  SCE_TOUCH_SAMPLING_STATE_START ; 
 int /*<<< orphan*/  curr_ctrl_info ; 
 int /*<<< orphan*/  input_autoconfigure_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  old_ctrl_info ; 
 scalar_t__ psp2_model ; 
 TYPE_1__ psp_joypad ; 
 int /*<<< orphan*/  psp_joypad_name (unsigned int) ; 
 int /*<<< orphan*/  sceCtrlGetControllerPortInfo (int /*<<< orphan*/ *) ; 
 scalar_t__ sceKernelGetModelForCDialog () ; 
 int /*<<< orphan*/  sceTouchSetSamplingState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool psp_joypad_init(void *data)
{
   unsigned i;
   unsigned players_count = DEFAULT_MAX_PADS;

   (void)data;

#if defined(VITA)
   psp2_model = sceKernelGetModelForCDialog();
   if (psp2_model != SCE_KERNEL_MODEL_VITATV)
   {
      sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
      sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
      players_count = 1;
   }
   sceCtrlGetControllerPortInfo(&curr_ctrl_info);
   memcpy(&old_ctrl_info, &curr_ctrl_info, sizeof(SceCtrlPortInfo));
#endif

   for (i = 0; i < players_count; i++)
      input_autoconfigure_connect(
            psp_joypad_name(i),
            NULL,
            psp_joypad.ident,
            i,
            0,
            0
            );

   return true;
}