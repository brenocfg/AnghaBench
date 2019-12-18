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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ frameBuffer; } ;
typedef  TYPE_1__ PrintConsole ;
typedef  int /*<<< orphan*/  Handle ;

/* Variables and functions */
 int /*<<< orphan*/  CFGU_GetModelNintendo2DS (int*) ; 
 int /*<<< orphan*/  CFGU_GetSystemModel (int*) ; 
 scalar_t__ FRONTEND_FORK_NONE ; 
 int /*<<< orphan*/  GSPGPU_WriteHWRegs (int,int*,int) ; 
 int /*<<< orphan*/  cfguExit () ; 
 int /*<<< orphan*/  csndExit () ; 
 scalar_t__ ctr_fork_mode ; 
 int* getThreadCommandBuffer () ; 
 int** gfxBottomFramebuffers ; 
 int /*<<< orphan*/  gfxExit () ; 
 int /*<<< orphan*/ ** gfxTopRightFramebuffers ; 
 int /*<<< orphan*/  mcuHwcExit () ; 
 int /*<<< orphan*/  ndspExit () ; 
 int /*<<< orphan*/  ptmuExit () ; 
 int /*<<< orphan*/  retro_main_log_file_deinit () ; 
 int /*<<< orphan*/  retro_main_log_file_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ srvGetServiceHandle (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svcCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcSendSyncRequest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbosity_enable () ; 
 int /*<<< orphan*/  wait_for_input () ; 

__attribute__((used)) static void frontend_ctr_deinit(void* data)
{
   Handle lcd_handle;
   u32 parallax_layer_reg_state;
   u8 not_2DS;
   u8 device_model = 0xFF;

   extern PrintConsole* currentConsole;

   (void)data;

#ifndef IS_SALAMANDER
   /* Note: frontend_ctr_deinit() is normally called when
    * forking to load new content. When this happens, the
    * log messages generated in frontend_ctr_exec() *must*
    * be printed to screen (provided bottom screen is not
    * turned off...), since the 'first core launch' warning
    * can prevent sdcard corruption. We therefore close any
    * existing log file, enable verbose logging and revert
    * to console output. (Normal logging will be resumed
    * once retroarch.cfg has been re-read) */
   retro_main_log_file_deinit();
   verbosity_enable();
   retro_main_log_file_init(NULL, false);

   if ((gfxBottomFramebuffers[0] == (u8*)currentConsole->frameBuffer)
         && (ctr_fork_mode == FRONTEND_FORK_NONE))
      wait_for_input();

   CFGU_GetModelNintendo2DS(&not_2DS);

   if (not_2DS && srvGetServiceHandle(&lcd_handle, "gsp::Lcd") >= 0)
   {
      u32* cmdbuf = getThreadCommandBuffer();
      cmdbuf[0]   = 0x00110040;
      cmdbuf[1]   = 2;
      svcSendSyncRequest(lcd_handle);
      svcCloseHandle(lcd_handle);
   }

   /* Only O3DS and O3DSXL support running in 'dual-framebuffer'
    * mode with the parallax barrier disabled
    * (i.e. these are the only platforms that can use
    * CTR_VIDEO_MODE_2D_400x240 and CTR_VIDEO_MODE_2D_800x240) */
   CFGU_GetSystemModel(&device_model); /* (0 = O3DS, 1 = O3DSXL, 2 = N3DS, 3 = 2DS, 4 = N3DSXL, 5 = N2DSXL) */
   if ((device_model == 0) || (device_model == 1))
   {
      parallax_layer_reg_state = (*(float*)0x1FF81080 == 0.0) ? 0x0 : 0x00010001;
      GSPGPU_WriteHWRegs(0x202000, &parallax_layer_reg_state, 4);
   }

   mcuHwcExit();
   ptmuExit();
   cfguExit();
   ndspExit();
   csndExit();
   gfxTopRightFramebuffers[0] = NULL;
   gfxTopRightFramebuffers[1] = NULL;
   gfxExit();
#endif
}