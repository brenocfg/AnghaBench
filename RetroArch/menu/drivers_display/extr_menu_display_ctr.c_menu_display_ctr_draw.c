#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ userdata; } ;
typedef  TYPE_5__ video_frame_info_t ;
struct ctr_texture {int width; int height; TYPE_8__* data; int /*<<< orphan*/  active_height; int /*<<< orphan*/  active_width; } ;
struct TYPE_17__ {scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; TYPE_2__* coords; scalar_t__ texture; } ;
typedef  TYPE_6__ menu_display_ctx_draw_t ;
struct TYPE_14__ {TYPE_8__* right; TYPE_8__* left; } ;
struct TYPE_15__ {TYPE_3__ top; } ;
struct TYPE_12__ {int size; int current; int buffer; } ;
struct TYPE_18__ {scalar_t__ video_mode; TYPE_4__ drawbuffers; TYPE_1__ vertex_cache; } ;
typedef  TYPE_7__ ctr_video_t ;
struct TYPE_19__ {int /*<<< orphan*/  v1; int /*<<< orphan*/  u1; scalar_t__ v0; scalar_t__ u0; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_8__ ctr_vertex_t ;
typedef  int /*<<< orphan*/  ctr_scale_vector_t ;
struct TYPE_13__ {float* color; } ;

/* Variables and functions */
 int COLOR_ABGR (int,int,int,int) ; 
 int CTRGU_ATTRIBFMT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTR_TOP_FRAMEBUFFER_HEIGHT ; 
 int CTR_TOP_FRAMEBUFFER_WIDTH ; 
 scalar_t__ CTR_VIDEO_MODE_2D_800x240 ; 
 scalar_t__ CTR_VIDEO_MODE_3D ; 
 int /*<<< orphan*/  GPU_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GPU_CONSTANT ; 
 int /*<<< orphan*/  GPU_DrawArray (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPU_GEOMETRY_PRIM ; 
 int /*<<< orphan*/  GPU_LINEAR ; 
 int /*<<< orphan*/  GPU_MODULATE ; 
 int /*<<< orphan*/  GPU_REPLACE ; 
 int /*<<< orphan*/  GPU_RGBA8 ; 
 int /*<<< orphan*/  GPU_SHORT ; 
 int /*<<< orphan*/  GPU_SetTexEnv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPU_SetViewport (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPU_TEVOPERANDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_TEVOP_RGB_SRC_COLOR ; 
 int /*<<< orphan*/  GPU_TEVSOURCES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_TEXTURE0 ; 
 int GPU_TEXTURE_MAG_FILTER (int /*<<< orphan*/ ) ; 
 int GPU_TEXTURE_MIN_FILTER (int /*<<< orphan*/ ) ; 
 int GPU_TEXTURE_WRAP_S (int /*<<< orphan*/ ) ; 
 int GPU_TEXTURE_WRAP_T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_TEXUNIT0 ; 
 int /*<<< orphan*/  VIRT_TO_PHYS (TYPE_8__*) ; 
 int /*<<< orphan*/  ctrGuSetAttributeBuffers (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ctrGuSetTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrGuSetVertexShaderFloatUniform (int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  ctr_set_scale_vector (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 

__attribute__((used)) static void menu_display_ctr_draw(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   struct ctr_texture *texture      = NULL;
   const float *color               = NULL;
   ctr_video_t             *ctr     = (ctr_video_t*)video_info->userdata;

   if (!ctr || !draw)
      return;

   texture            = (struct ctr_texture*)draw->texture;
   color              = draw->coords->color;

   if (!texture)
      return;

   ctr_scale_vector_t scale_vector;
   ctr_set_scale_vector(&scale_vector,
         CTR_TOP_FRAMEBUFFER_WIDTH, CTR_TOP_FRAMEBUFFER_HEIGHT,
         texture->width, texture->height);
   ctrGuSetVertexShaderFloatUniform(0, (float*)&scale_vector, 1);

   if ((ctr->vertex_cache.size - (ctr->vertex_cache.current - ctr->vertex_cache.buffer)) < 1)
      ctr->vertex_cache.current = ctr->vertex_cache.buffer;

   ctr_vertex_t* v = ctr->vertex_cache.current++;

   v->x0 = draw->x;
   v->y0 = 240 - draw->height - draw->y;
   v->x1 = v->x0 + draw->width;
   v->y1 = v->y0 + draw->height;
   v->u0 = 0;
   v->v0 = 0;
   v->u1 = texture->active_width;
   v->v1 = texture->active_height;

   ctrGuSetAttributeBuffers(2,
         VIRT_TO_PHYS(v),
         CTRGU_ATTRIBFMT(GPU_SHORT, 4) << 0 |
         CTRGU_ATTRIBFMT(GPU_SHORT, 4) << 4,
         sizeof(ctr_vertex_t));

   color = draw->coords->color;
   int colorR = (int)((*color++)*255.f);
   int colorG = (int)((*color++)*255.f);
   int colorB = (int)((*color++)*255.f);
   int colorA = (int)((*color++)*255.f);

   GPU_SetTexEnv(0,
         GPU_TEVSOURCES(GPU_TEXTURE0, GPU_CONSTANT, 0),
         GPU_TEVSOURCES(GPU_TEXTURE0, GPU_CONSTANT, 0),
         0,
         0,
         GPU_MODULATE, GPU_MODULATE,
         COLOR_ABGR(colorR,colorG,colorB,colorA)
         );

#if 0
   GPU_SetTexEnv(0,
         GPU_TEVSOURCES(GPU_CONSTANT, GPU_CONSTANT, 0),
         GPU_TEVSOURCES(GPU_CONSTANT, GPU_CONSTANT, 0),
         0,
         GPU_TEVOPERANDS(GPU_TEVOP_RGB_SRC_COLOR, GPU_TEVOP_RGB_SRC_COLOR, 0),
         GPU_REPLACE, GPU_REPLACE,
         0x3FFFFFFF);
#endif

   ctrGuSetTexture(GPU_TEXUNIT0, VIRT_TO_PHYS(texture->data), texture->width, texture->height,
         GPU_TEXTURE_MAG_FILTER(GPU_LINEAR)  | GPU_TEXTURE_MIN_FILTER(GPU_LINEAR) |
         GPU_TEXTURE_WRAP_S(GPU_CLAMP_TO_EDGE) | GPU_TEXTURE_WRAP_T(GPU_CLAMP_TO_EDGE),
         GPU_RGBA8);

   GPU_SetViewport(NULL,
         VIRT_TO_PHYS(ctr->drawbuffers.top.left),
         0, 0, CTR_TOP_FRAMEBUFFER_HEIGHT,
         ctr->video_mode == CTR_VIDEO_MODE_2D_800x240 ?
         CTR_TOP_FRAMEBUFFER_WIDTH * 2 : CTR_TOP_FRAMEBUFFER_WIDTH);

   GPU_DrawArray(GPU_GEOMETRY_PRIM, 0, 1);

   if (ctr->video_mode == CTR_VIDEO_MODE_3D)
   {
      GPU_SetViewport(NULL,
            VIRT_TO_PHYS(ctr->drawbuffers.top.right),
            0, 0, CTR_TOP_FRAMEBUFFER_HEIGHT,
            CTR_TOP_FRAMEBUFFER_WIDTH);
      GPU_DrawArray(GPU_GEOMETRY_PRIM, 0, 1);
   }

   GPU_SetTexEnv(0, GPU_TEXTURE0, GPU_TEXTURE0, 0, 0, GPU_REPLACE, GPU_REPLACE, 0);
#if 0
   printf("(%i,%i,%i,%i) , (%i,%i)\n", (int)draw->x,
         (int)draw->y, (int)draw->width, (int)draw->height,
         texture->width, texture->height);
#endif
}