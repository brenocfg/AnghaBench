#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int input_scale; int rgb32; } ;
typedef  TYPE_1__ video_info_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int scale; int rgb32; int should_resize; } ;
typedef  TYPE_2__ gx_video_t ;
struct TYPE_7__ {int width; int height; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  Mtx44 ;

/* Variables and functions */
 int /*<<< orphan*/  DCFlushRange (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_AF_NONE ; 
 int /*<<< orphan*/  GX_ALWAYS ; 
 int /*<<< orphan*/  GX_BL_INVSRCALPHA ; 
 int /*<<< orphan*/  GX_BL_SRCALPHA ; 
 int /*<<< orphan*/  GX_BM_BLEND ; 
 int /*<<< orphan*/  GX_CLIP_DISABLE ; 
 int /*<<< orphan*/  GX_CLR_RGBA ; 
 int /*<<< orphan*/  GX_COLOR0A0 ; 
 int /*<<< orphan*/  GX_CULL_NONE ; 
 int /*<<< orphan*/  GX_ClearVtxDesc () ; 
 int /*<<< orphan*/  GX_DF_NONE ; 
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_ENABLE ; 
 int /*<<< orphan*/  GX_F32 ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_INDEX8 ; 
 int /*<<< orphan*/  GX_InvVtxCache () ; 
 int /*<<< orphan*/  GX_LIGHTNULL ; 
 int /*<<< orphan*/  GX_LO_CLEAR ; 
 int /*<<< orphan*/  GX_LoadProjectionMtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_MODULATE ; 
 int /*<<< orphan*/  GX_ORTHOGRAPHIC ; 
 int /*<<< orphan*/  GX_POS_XYZ ; 
 int /*<<< orphan*/  GX_RGBA8 ; 
 int /*<<< orphan*/  GX_SRC_REG ; 
 int /*<<< orphan*/  GX_SRC_VTX ; 
 int /*<<< orphan*/  GX_SetAlphaUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetArray (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_SetBlendMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetChanCtrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetClipMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetColorUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetCullMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetNumChans (int) ; 
 int /*<<< orphan*/  GX_SetNumTexGens (int) ; 
 int /*<<< orphan*/  GX_SetTevOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevOrder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetVtxAttrFmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetVtxDesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetZMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TEVSTAGE0 ; 
 int /*<<< orphan*/  GX_TEXCOORD0 ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TEX_ST ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  GX_VA_CLR0 ; 
 int /*<<< orphan*/  GX_VA_POS ; 
 int /*<<< orphan*/  GX_VA_TEX0 ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int RARCH_SCALE_BASE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_ptr ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_4__ g_tex ; 
 int /*<<< orphan*/  guOrtho (int /*<<< orphan*/ ,int,int,int,int,double,double) ; 
 int /*<<< orphan*/  init_texture (void*,int,int) ; 
 int /*<<< orphan*/  memalign (int,int) ; 
 int /*<<< orphan*/  referenceRetraceCount ; 
 int /*<<< orphan*/  retraceCount ; 
 int /*<<< orphan*/  vertex_ptr ; 
 int /*<<< orphan*/  verts ; 

__attribute__((used)) static void init_vtx(void *data, const video_info_t *video)
{
   Mtx44 m;
   gx_video_t *gx      = (gx_video_t*)data;
   uint32_t level      = 0;
   _CPU_ISR_Disable(level);
   referenceRetraceCount = retraceCount;
   _CPU_ISR_Restore(level);

   GX_SetCullMode(GX_CULL_NONE);
   GX_SetClipMode(GX_CLIP_DISABLE);
   GX_SetZMode(GX_ENABLE, GX_ALWAYS, GX_ENABLE);
   GX_SetColorUpdate(GX_TRUE);
   GX_SetAlphaUpdate(GX_FALSE);

   guOrtho(m, 1, -1, -1, 1, 0.4, 0.6);
   GX_LoadProjectionMtx(m, GX_ORTHOGRAPHIC);

   GX_ClearVtxDesc();
   GX_SetVtxDesc(GX_VA_POS, GX_INDEX8);
   GX_SetVtxDesc(GX_VA_TEX0, GX_INDEX8);
   GX_SetVtxDesc(GX_VA_CLR0, GX_INDEX8);

   GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
   GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
   GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
   GX_SetArray(GX_VA_POS, verts, 3 * sizeof(float));
   GX_SetArray(GX_VA_TEX0, vertex_ptr, 2 * sizeof(float));
   GX_SetArray(GX_VA_CLR0, color_ptr, 4 * sizeof(u8));

   GX_SetNumTexGens(1);
   GX_SetNumChans(1);
   GX_SetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG,
         GX_SRC_VTX, GX_LIGHTNULL, GX_DF_NONE, GX_AF_NONE);
   GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
   GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
   GX_InvVtxCache();

   GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA,
         GX_BL_INVSRCALPHA, GX_LO_CLEAR);

   if (gx->scale != video->input_scale || gx->rgb32 != video->rgb32)
   {
      RARCH_LOG("[GX]: Reallocate texture.\n");
      free(g_tex.data);
      g_tex.data = memalign(32,
            RARCH_SCALE_BASE * RARCH_SCALE_BASE * video->input_scale *
            video->input_scale * (video->rgb32 ? 4 : 2));
      g_tex.width = g_tex.height = RARCH_SCALE_BASE * video->input_scale;

      if (!g_tex.data)
      {
         RARCH_ERR("[GX]: Error allocating video texture\n");
         exit(1);
      }
   }

   DCFlushRange(g_tex.data, (g_tex.width *
         g_tex.height * video->rgb32) ? 4 : 2);

   gx->rgb32 = video->rgb32;
   gx->scale = video->input_scale;
   gx->should_resize = true;

   init_texture(data, g_tex.width, g_tex.height);
   GX_Flush();
}