#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_BOTTOM ; 
 int /*<<< orphan*/  GFX_TOP ; 
 int /*<<< orphan*/  GSP_BGR8_OES ; 
 int /*<<< orphan*/  GSP_RGB565_OES ; 
 int /*<<< orphan*/  __ctr_patch_services ; 
 void* audio_ctr_csnd ; 
 void* audio_ctr_dsp ; 
 void* audio_null ; 
 int /*<<< orphan*/  cfguInit () ; 
 int /*<<< orphan*/  consoleInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ csndInit () ; 
 int /*<<< orphan*/  ctr_check_dspfirm () ; 
 scalar_t__* gfxBottomFramebuffers ; 
 int /*<<< orphan*/  gfxInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfxSet3D (int) ; 
 int /*<<< orphan*/  gfxSetFramebufferInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* gfxTopLeftFramebuffers ; 
 scalar_t__* gfxTopRightFramebuffers ; 
 scalar_t__ linearAlloc (int) ; 
 int /*<<< orphan*/  linearFree (scalar_t__) ; 
 int /*<<< orphan*/  mcuHwcInit () ; 
 scalar_t__ ndspInit () ; 
 int /*<<< orphan*/  osSetSpeedupEnable (int) ; 
 int /*<<< orphan*/  ptmuInit () ; 
 int /*<<< orphan*/  svchax_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbosity_enable () ; 

__attribute__((used)) static void frontend_ctr_init(void* data)
{
#ifndef IS_SALAMANDER
   (void)data;

   verbosity_enable();

   gfxInit(GSP_BGR8_OES, GSP_RGB565_OES, false);

   u32 topSize               = 400 * 240 * 3;
   u32 bottomSize            = 320 * 240 * 2;
   linearFree(gfxTopLeftFramebuffers [0]);
   linearFree(gfxTopLeftFramebuffers [1]);
   linearFree(gfxBottomFramebuffers  [0]);
   linearFree(gfxBottomFramebuffers  [1]);
   linearFree(gfxTopRightFramebuffers[0]);
   linearFree(gfxTopRightFramebuffers[1]);

   gfxTopLeftFramebuffers [0] = linearAlloc(topSize * 2);
   gfxTopRightFramebuffers[0] = gfxTopLeftFramebuffers[0] + topSize;

   gfxTopLeftFramebuffers [1] = linearAlloc(topSize * 2);
   gfxTopRightFramebuffers[1] = gfxTopLeftFramebuffers[1] + topSize;

   gfxBottomFramebuffers  [0] = linearAlloc(bottomSize);
   gfxBottomFramebuffers  [1] = linearAlloc(bottomSize);

   gfxSetFramebufferInfo(GFX_TOP, 0);
   gfxSetFramebufferInfo(GFX_BOTTOM, 0);

   gfxSet3D(true);
   consoleInit(GFX_BOTTOM, NULL);

   /* enable access to all service calls when possible. */
   if (svchax_init)
   {
      osSetSpeedupEnable(false);
      svchax_init(__ctr_patch_services);
   }
   osSetSpeedupEnable(true);

   if (csndInit() != 0)
      audio_ctr_csnd = audio_null;
   ctr_check_dspfirm();
   if (ndspInit() != 0)
      audio_ctr_dsp = audio_null;
   cfguInit();
   ptmuInit();
   mcuHwcInit();
#endif
}