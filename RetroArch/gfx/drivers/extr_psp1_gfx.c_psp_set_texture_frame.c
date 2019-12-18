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
struct TYPE_3__ {int /*<<< orphan*/  frame_coords; int /*<<< orphan*/  frame; int /*<<< orphan*/  dList; } ;
struct TYPE_4__ {TYPE_1__ menu; int /*<<< orphan*/  main_dList; } ;
typedef  TYPE_2__ psp1_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  GU_ADD ; 
 int /*<<< orphan*/  GU_BLEND ; 
 int /*<<< orphan*/  GU_DIRECT ; 
 int /*<<< orphan*/  GU_FALSE ; 
 int /*<<< orphan*/  GU_FIX ; 
 int /*<<< orphan*/  GU_LINEAR ; 
 int /*<<< orphan*/  GU_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GU_PSM_4444 ; 
 int /*<<< orphan*/  GU_SEND ; 
 int /*<<< orphan*/  GU_SPRITES ; 
 int /*<<< orphan*/  GU_SRC_ALPHA ; 
 int /*<<< orphan*/  GU_TCC_RGB ; 
 int GU_TEXTURE_32BITF ; 
 int /*<<< orphan*/  GU_TFX_REPLACE ; 
 int GU_TRANSFORM_2D ; 
 int GU_VERTEX_32BITF ; 
 int /*<<< orphan*/  PSP_FRAME_VERTEX_COUNT ; 
 int /*<<< orphan*/  SCEGU_SCR_HEIGHT ; 
 int /*<<< orphan*/  SCEGU_SCR_WIDTH ; 
 int /*<<< orphan*/  next_pow2 (unsigned int) ; 
 int /*<<< orphan*/  psp_set_screen_coords (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_set_tex_coords (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 int /*<<< orphan*/  sceGuBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sceGuCopyImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuDrawArray (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuFinish () ; 
 int /*<<< orphan*/  sceGuStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelDcacheWritebackRange (void const*,unsigned int) ; 

__attribute__((used)) static void psp_set_texture_frame(void *data, const void *frame, bool rgb32,
                               unsigned width, unsigned height, float alpha)
{
   psp1_video_t *psp = (psp1_video_t*)data;

   (void) rgb32;
   (void) alpha;

#ifdef DEBUG
   /* psp->menu.frame buffer size is (480 * 272)*2 Bytes */
   retro_assert((width*height) < (480 * 272));
#endif

   psp_set_screen_coords(psp->menu.frame_coords, 0, 0,
         SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, 0);
   psp_set_tex_coords(psp->menu.frame_coords, width, height);

   sceKernelDcacheWritebackRange(frame, width * height * 2);

   sceGuStart(GU_DIRECT, psp->main_dList);
   sceGuCopyImage(GU_PSM_4444, 0, 0, width, height, width,
         (void*)frame, 0, 0, width, psp->menu.frame);
   sceGuFinish();

   sceGuStart(GU_SEND, psp->menu.dList);
   sceGuTexMode(GU_PSM_4444, 0, 0, GU_FALSE);
   sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
   sceGuTexFilter(GU_LINEAR, GU_LINEAR);
   sceGuTexImage(0, next_pow2(width), next_pow2(height), width, psp->menu.frame);
   sceGuEnable(GU_BLEND);

#if 0
   /* default blending */
   sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
#endif
   sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xF0F0F0F0, 0x0F0F0F0F);
;
   sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF |
         GU_TRANSFORM_2D, PSP_FRAME_VERTEX_COUNT, NULL,
         psp->menu.frame_coords);
   sceGuFinish();

}