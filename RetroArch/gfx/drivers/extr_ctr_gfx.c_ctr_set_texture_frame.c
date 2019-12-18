#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int texture_width; int texture_height; int /*<<< orphan*/  texture_swizzled; TYPE_3__* texture_linear; TYPE_3__* frame_coords; } ;
struct TYPE_6__ {int menu_texture_frame_enable; TYPE_1__ menu; } ;
typedef  TYPE_2__ ctr_video_t ;
typedef  int /*<<< orphan*/  ctr_vertex_t ;
struct TYPE_7__ {unsigned int x0; int y0; unsigned int x1; unsigned int y1; unsigned int u1; unsigned int v1; scalar_t__ v0; scalar_t__ u0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRGU_RGBA4444 ; 
 int CTR_TOP_FRAMEBUFFER_HEIGHT ; 
 int /*<<< orphan*/  CTR_TOP_FRAMEBUFFER_WIDTH ; 
 int /*<<< orphan*/  GSPGPU_FlushDataCache (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ctrGuCopyImage (int,TYPE_3__*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void ctr_set_texture_frame(void* data, const void* frame, bool rgb32,
                                  unsigned width, unsigned height, float alpha)
{
   int i;
   ctr_video_t* ctr = (ctr_video_t*)data;
   int line_width = width;
   (void)rgb32;
   (void)alpha;

   if(!ctr || !frame)
      return;

   if (line_width > ctr->menu.texture_width)
      line_width = ctr->menu.texture_width;

   if (height > (unsigned)ctr->menu.texture_height)
      height = (unsigned)ctr->menu.texture_height;

   const uint16_t* src = frame;
   uint16_t* dst = (uint16_t*)ctr->menu.texture_linear;
   for (i = 0; i < height; i++)
   {
      memcpy(dst, src, line_width * sizeof(uint16_t));
      dst += ctr->menu.texture_width;
      src += width;
   }

   ctr->menu.frame_coords->x0 = (CTR_TOP_FRAMEBUFFER_WIDTH - width) / 2;
   ctr->menu.frame_coords->y0 = (CTR_TOP_FRAMEBUFFER_HEIGHT - height) / 2;
   ctr->menu.frame_coords->x1 = ctr->menu.frame_coords->x0 + width;
   ctr->menu.frame_coords->y1 = ctr->menu.frame_coords->y0 + height;
   ctr->menu.frame_coords->u0 = 0;
   ctr->menu.frame_coords->v0 = 0;
   ctr->menu.frame_coords->u1 = width;
   ctr->menu.frame_coords->v1 = height;
   GSPGPU_FlushDataCache(ctr->menu.frame_coords, sizeof(ctr_vertex_t));
   ctr->menu_texture_frame_enable = true;
   GSPGPU_FlushDataCache(ctr->menu.texture_linear,
                         ctr->menu.texture_width * ctr->menu.texture_height * sizeof(uint16_t));

   ctrGuCopyImage(false, ctr->menu.texture_linear, ctr->menu.texture_width, ctr->menu.texture_height, CTRGU_RGBA4444,false,
                  ctr->menu.texture_swizzled, ctr->menu.texture_width, CTRGU_RGBA4444,  true);
}