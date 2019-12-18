#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  context_storage; int /*<<< orphan*/  dList; scalar_t__ active; } ;
struct TYPE_5__ {int hw_render; int vblank_not_reached; int bpp_log2; TYPE_1__ menu; int /*<<< orphan*/  frame_dList; int /*<<< orphan*/  texture; scalar_t__ rgb32; scalar_t__ frame_coords; int /*<<< orphan*/  tex_filter; int /*<<< orphan*/  main_dList; scalar_t__ should_resize; int /*<<< orphan*/  draw_buffer; scalar_t__ vsync; } ;
typedef  TYPE_2__ psp1_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_GU_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GU_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GU_DIRECT ; 
 int /*<<< orphan*/  GU_PSM_5650 ; 
 int /*<<< orphan*/  GU_PSM_8888 ; 
 int /*<<< orphan*/  GU_SPRITES ; 
 int /*<<< orphan*/  GU_TAIL ; 
 int GU_TEXTURE_32BITF ; 
 int GU_TRANSFORM_2D ; 
 int GU_VERTEX_32BITF ; 
 int /*<<< orphan*/  PSP_FRAME_VERTEX_COUNT ; 
 void const* RETRO_HW_FRAME_BUFFER_VALID ; 
 int /*<<< orphan*/  menu_driver_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_pow2 (unsigned int) ; 
 int /*<<< orphan*/  pspDebugScreenPuts (char const*) ; 
 int /*<<< orphan*/  pspDebugScreenSetBase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pspDebugScreenSetXY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_set_tex_coords (scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  psp_update_viewport (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceDisplayWaitVblankStart () ; 
 int /*<<< orphan*/  sceGuCallList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuCopyImage (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuDrawArray (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sceGuFinish () ; 
 int /*<<< orphan*/  sceGuSendList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceGuStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuSwapBuffers () ; 
 int /*<<< orphan*/  sceGuSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelDcacheWritebackRange (void const*,unsigned int) ; 

__attribute__((used)) static bool psp_frame(void *data, const void *frame,
      unsigned width, unsigned height, uint64_t frame_count,
      unsigned pitch, const char *msg, video_frame_info_t *video_info)
{
   psp1_video_t *psp                       = (psp1_video_t*)data;

   if (!width || !height)
      return false;

   if (((uint32_t)frame&0x04000000) || (frame == RETRO_HW_FRAME_BUFFER_VALID))
      psp->hw_render = true;
   else if (frame)
      psp->hw_render = false;

   if (!psp->hw_render)
      sceGuSync(0, 0); /* let the core decide when to sync when HW_RENDER */

   if (msg) 
   {
      pspDebugScreenSetBase(psp->draw_buffer);
      pspDebugScreenSetXY(0,0);
      pspDebugScreenPuts(msg);
   }
      

   if ((psp->vsync)&&(psp->vblank_not_reached))
      sceDisplayWaitVblankStart();

   psp->vblank_not_reached = true;

   psp->draw_buffer = FROM_GU_POINTER(sceGuSwapBuffers());

   if (psp->should_resize)
      psp_update_viewport(psp, video_info);

   psp_set_tex_coords(psp->frame_coords, width, height);

   sceGuStart(GU_DIRECT, psp->main_dList);

   sceGuTexFilter(psp->tex_filter, psp->tex_filter);
   sceGuClear(GU_COLOR_BUFFER_BIT);

   /* frame in VRAM ? texture/palette was
    * set in core so draw directly */
   if (psp->hw_render)
      sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF |
            GU_TRANSFORM_2D, PSP_FRAME_VERTEX_COUNT, NULL,
            (void*)(psp->frame_coords));
   else
   {
      if (frame)
      {
         sceKernelDcacheWritebackRange(frame,pitch * height);
         sceGuCopyImage(psp->rgb32? GU_PSM_8888 : GU_PSM_5650, ((u32)frame & 0xF) >> psp->bpp_log2,
               0, width, height, pitch >> psp->bpp_log2,
               (void*)((u32)frame & ~0xF), 0, 0, width, psp->texture);
      }
      sceGuTexImage(0, next_pow2(width), next_pow2(height), width, psp->texture);
      sceGuCallList(psp->frame_dList);
   }

   sceGuFinish();

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   if(psp->menu.active)
   {
      sceGuSendList(GU_TAIL, psp->menu.dList, &(psp->menu.context_storage));
      sceGuSync(0, 0);
   }

   return true;
}