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
typedef  int /*<<< orphan*/  uint32_t ;
struct scaler_ctx {int in_width; int in_height; int out_width; int out_height; int in_stride; int out_stride; int /*<<< orphan*/  scaler_type; int /*<<< orphan*/  out_fmt; int /*<<< orphan*/  in_fmt; } ;
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {int pbo_readback_enable; int /*<<< orphan*/ * pbo_readback; TYPE_1__ vp; struct scaler_ctx pbo_readback_scaler; } ;
typedef  TYPE_2__ gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SCALER_FMT_ARGB8888 ; 
 int /*<<< orphan*/  SCALER_FMT_BGR24 ; 
 int /*<<< orphan*/  SCALER_TYPE_POINT ; 
 int /*<<< orphan*/  gl2_renderchain_bind_pbo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_renderchain_init_pbo (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl2_renderchain_unbind_pbo () ; 
 int /*<<< orphan*/  glDeleteBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scaler_ctx_gen_filter (struct scaler_ctx*) ; 

__attribute__((used)) static bool gl2_init_pbo_readback(gl_t *gl)
{
#if !defined(HAVE_OPENGLES2) && !defined(HAVE_PSGL)
   unsigned i;

   glGenBuffers(4, gl->pbo_readback);

   for (i = 0; i < 4; i++)
   {
      gl2_renderchain_bind_pbo(gl->pbo_readback[i]);
      gl2_renderchain_init_pbo(gl->vp.width *
            gl->vp.height * sizeof(uint32_t), NULL);
   }
   gl2_renderchain_unbind_pbo();

#ifndef HAVE_OPENGLES3
   {
      struct scaler_ctx *scaler = &gl->pbo_readback_scaler;
      scaler->in_width          = gl->vp.width;
      scaler->in_height         = gl->vp.height;
      scaler->out_width         = gl->vp.width;
      scaler->out_height        = gl->vp.height;
      scaler->in_stride         = gl->vp.width * sizeof(uint32_t);
      scaler->out_stride        = gl->vp.width * 3;
      scaler->in_fmt            = SCALER_FMT_ARGB8888;
      scaler->out_fmt           = SCALER_FMT_BGR24;
      scaler->scaler_type       = SCALER_TYPE_POINT;

      if (!scaler_ctx_gen_filter(scaler))
      {
         gl->pbo_readback_enable = false;
         RARCH_ERR("[GL]: Failed to initialize pixel conversion for PBO.\n");
         glDeleteBuffers(4, gl->pbo_readback);
         return false;
      }
   }
#endif

   return true;
#else
   /* If none of these are bound, we have to assume
    * we are not going to use PBOs */
   return false;
#endif
}