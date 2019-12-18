#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  frame_coords; } ;
struct TYPE_5__ {int /*<<< orphan*/  left; } ;
struct TYPE_6__ {TYPE_1__ top; } ;
struct TYPE_8__ {int p3d_event_pending; scalar_t__ video_mode; size_t current_buffer_top; scalar_t__ supports_parallax_disable; TYPE_3__ menu; TYPE_2__ drawbuffers; int /*<<< orphan*/  shader; } ;
typedef  TYPE_4__ ctr_video_t ;
typedef  int /*<<< orphan*/  ctr_vertex_t ;
typedef  int /*<<< orphan*/  Handle ;
typedef  scalar_t__ APT_HookType ;

/* Variables and functions */
 scalar_t__ APTHOOK_ONRESTORE ; 
 scalar_t__ APTHOOK_ONSUSPEND ; 
 int /*<<< orphan*/  CFGU_GetModelNintendo2DS (scalar_t__*) ; 
 int CTRGU_ATTRIBFMT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTR_TOP_FRAMEBUFFER_HEIGHT ; 
 int /*<<< orphan*/  CTR_TOP_FRAMEBUFFER_WIDTH ; 
 scalar_t__ CTR_VIDEO_MODE_2D_400x240 ; 
 int /*<<< orphan*/  GPUCMD_AddMaskedWrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPUCMD_SetBufferOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPUREG_EARLYDEPTH_TEST1 ; 
 int /*<<< orphan*/  GPUREG_EARLYDEPTH_TEST2 ; 
 int /*<<< orphan*/  GPU_ALWAYS ; 
 int /*<<< orphan*/  GPU_BLEND_ADD ; 
 int /*<<< orphan*/  GPU_CULL_NONE ; 
 int /*<<< orphan*/  GPU_DepthMap (float,float) ; 
 int /*<<< orphan*/  GPU_Finalize () ; 
 int /*<<< orphan*/  GPU_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GPU_PREVIOUS ; 
 int /*<<< orphan*/  GPU_REPLACE ; 
 int /*<<< orphan*/  GPU_SHORT ; 
 int /*<<< orphan*/  GPU_SRC_ALPHA ; 
 int /*<<< orphan*/  GPU_STENCIL_KEEP ; 
 int /*<<< orphan*/  GPU_SetAlphaBlending (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_SetAlphaTest (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPU_SetBlendingColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_SetDepthTestAndWriteMask (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_SetFaceCulling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_SetStencilOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_SetStencilTest (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  GPU_SetTexEnv (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_SetTextureEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_SetViewport (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_TEXTURE0 ; 
 int /*<<< orphan*/  GPU_TEXUNIT0 ; 
 int /*<<< orphan*/  GPU_WRITE_COLOR ; 
 int /*<<< orphan*/  GSPGPU_EVENT_P3D ; 
 int /*<<< orphan*/  GSPGPU_FlushDataCache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VIRT_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrGuFlushAndRun (int) ; 
 int /*<<< orphan*/  ctrGuSetAttributeBuffers (int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ctr_bottom_screen_enabled ; 
 int /*<<< orphan*/  ctr_set_parallax_layer (int) ; 
 int* getThreadCommandBuffer () ; 
 int /*<<< orphan*/ * gfxTopLeftFramebuffers ; 
 int /*<<< orphan*/ * gfxTopRightFramebuffers ; 
 int /*<<< orphan*/  gspWaitForEvent (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shaderProgramUse (int /*<<< orphan*/ *) ; 
 scalar_t__ srvGetServiceHandle (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svcCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcSendSyncRequest (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctr_lcd_aptHook(APT_HookType hook, void* param)
{
   ctr_video_t *ctr  = (ctr_video_t*)param;

   if(!ctr)
      return;

   if(hook == APTHOOK_ONRESTORE)
   {
      GPUCMD_SetBufferOffset(0);
      shaderProgramUse(&ctr->shader);

      GPU_SetViewport(NULL,
                      VIRT_TO_PHYS(ctr->drawbuffers.top.left),
                      0, 0, CTR_TOP_FRAMEBUFFER_HEIGHT, CTR_TOP_FRAMEBUFFER_WIDTH);

      GPU_DepthMap(-1.0f, 0.0f);
      GPU_SetFaceCulling(GPU_CULL_NONE);
      GPU_SetStencilTest(false, GPU_ALWAYS, 0x00, 0xFF, 0x00);
      GPU_SetStencilOp(GPU_STENCIL_KEEP, GPU_STENCIL_KEEP, GPU_STENCIL_KEEP);
      GPU_SetBlendingColor(0, 0, 0, 0);
      GPU_SetDepthTestAndWriteMask(false, GPU_ALWAYS, GPU_WRITE_COLOR);
      GPUCMD_AddMaskedWrite(GPUREG_EARLYDEPTH_TEST1, 0x1, 0);
      GPUCMD_AddWrite(GPUREG_EARLYDEPTH_TEST2, 0);
      GPU_SetAlphaBlending(GPU_BLEND_ADD, GPU_BLEND_ADD,
                           GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA,
                           GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA);
      GPU_SetAlphaTest(false, GPU_ALWAYS, 0x00);
      GPU_SetTextureEnable(GPU_TEXUNIT0);
      GPU_SetTexEnv(0, GPU_TEXTURE0, GPU_TEXTURE0, 0, 0, GPU_REPLACE, GPU_REPLACE, 0);
      GPU_SetTexEnv(1, GPU_PREVIOUS, GPU_PREVIOUS, 0, 0, 0, 0, 0);
      GPU_SetTexEnv(2, GPU_PREVIOUS, GPU_PREVIOUS, 0, 0, 0, 0, 0);
      GPU_SetTexEnv(3, GPU_PREVIOUS, GPU_PREVIOUS, 0, 0, 0, 0, 0);
      GPU_SetTexEnv(4, GPU_PREVIOUS, GPU_PREVIOUS, 0, 0, 0, 0, 0);
      GPU_SetTexEnv(5, GPU_PREVIOUS, GPU_PREVIOUS, 0, 0, 0, 0, 0);
      ctrGuSetAttributeBuffers(2,
                               VIRT_TO_PHYS(ctr->menu.frame_coords),
                               CTRGU_ATTRIBFMT(GPU_SHORT, 4) << 0 |
                               CTRGU_ATTRIBFMT(GPU_SHORT, 4) << 4,
                               sizeof(ctr_vertex_t));
      GPU_Finalize();
      ctrGuFlushAndRun(true);
      gspWaitForEvent(GSPGPU_EVENT_P3D, false);
      ctr->p3d_event_pending = false;
   }

   if((hook == APTHOOK_ONSUSPEND) && (ctr->video_mode == CTR_VIDEO_MODE_2D_400x240))
   {
      memcpy(gfxTopRightFramebuffers[ctr->current_buffer_top],
            gfxTopLeftFramebuffers[ctr->current_buffer_top],
            400 * 240 * 3);
      GSPGPU_FlushDataCache(gfxTopRightFramebuffers[ctr->current_buffer_top], 400 * 240 * 3);
   }

   if ((hook == APTHOOK_ONSUSPEND) && ctr->supports_parallax_disable)
      ctr_set_parallax_layer(*(float*)0x1FF81080 != 0.0);

   if((hook == APTHOOK_ONSUSPEND) || (hook == APTHOOK_ONRESTORE))
   {
      Handle lcd_handle;
      u8 not_2DS;
      CFGU_GetModelNintendo2DS(&not_2DS);
      if(not_2DS && srvGetServiceHandle(&lcd_handle, "gsp::Lcd") >= 0)
      {
         u32 *cmdbuf = getThreadCommandBuffer();
         cmdbuf[0] = ((hook == APTHOOK_ONSUSPEND) || ctr_bottom_screen_enabled)? 0x00110040: 0x00120040;
         cmdbuf[1] = 2;
         svcSendSyncRequest(lcd_handle);
         svcCloseHandle(lcd_handle);
      }
   }
}