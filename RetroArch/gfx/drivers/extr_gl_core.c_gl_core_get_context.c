#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct retro_hw_render_callback {scalar_t__ context_type; unsigned int version_major; unsigned int version_minor; } ;
struct TYPE_12__ {int /*<<< orphan*/  video_context_driver; } ;
struct TYPE_13__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_14__ {int use_shared_context; void* ctx_data; } ;
typedef  TYPE_3__ gl_core_t ;
struct TYPE_15__ {scalar_t__ flags; } ;
typedef  TYPE_4__ gfx_ctx_flags_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* bind_hw_render ) (void*,int) ;} ;
typedef  TYPE_5__ gfx_ctx_driver_t ;
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;

/* Variables and functions */
 int /*<<< orphan*/  BIT32_SET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_GL_CORE_CONTEXT ; 
 int GFX_CTX_OPENGL_API ; 
 int GFX_CTX_OPENGL_ES_API ; 
 scalar_t__ RETRO_HW_CONTEXT_NONE ; 
 scalar_t__ RETRO_HW_CONTEXT_OPENGLES_VERSION ; 
 scalar_t__ RETRO_HW_CONTEXT_OPENGL_CORE ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  gl_query_core_context_set (int) ; 
 int /*<<< orphan*/  stub1 (void*,int) ; 
 TYPE_5__* video_context_driver_init_first (TYPE_3__*,int /*<<< orphan*/ ,int,unsigned int,unsigned int,int,void**) ; 
 int /*<<< orphan*/  video_context_driver_set_flags (TYPE_4__*) ; 
 struct retro_hw_render_callback* video_driver_get_hw_context () ; 

__attribute__((used)) static const gfx_ctx_driver_t *gl_core_get_context(gl_core_t *gl)
{
   unsigned major;
   unsigned minor;
   enum gfx_ctx_api api;
   gfx_ctx_flags_t flags;
   const gfx_ctx_driver_t *gfx_ctx      = NULL;
   void                      *ctx_data  = NULL;
   settings_t                 *settings = config_get_ptr();
   struct retro_hw_render_callback *hwr = video_driver_get_hw_context();

#ifdef HAVE_OPENGLES3
   api = GFX_CTX_OPENGL_ES_API;
   major = 3;
   minor = 0;
   if (hwr && hwr->context_type == RETRO_HW_CONTEXT_OPENGLES_VERSION)
   {
      major = hwr->version_major;
      minor = hwr->version_minor;
   }
#else
   api   = GFX_CTX_OPENGL_API;
   if (hwr && hwr->context_type != RETRO_HW_CONTEXT_NONE)
   {
      major = hwr->version_major;
      minor = hwr->version_minor;
      gl_query_core_context_set(hwr->context_type == RETRO_HW_CONTEXT_OPENGL_CORE);
      if (hwr->context_type == RETRO_HW_CONTEXT_OPENGL_CORE)
      {
         flags.flags = 0;
         BIT32_SET(flags.flags, GFX_CTX_FLAGS_GL_CORE_CONTEXT);
         video_context_driver_set_flags(&flags);
      }
   }
   else
   {
      major = 3;
      minor = 2;
      gl_query_core_context_set(true);
      flags.flags = 0;
      BIT32_SET(flags.flags, GFX_CTX_FLAGS_GL_CORE_CONTEXT);
      video_context_driver_set_flags(&flags);
   }
#endif

   /* Force shared context. */
   if (hwr)
      gl->use_shared_context = hwr->context_type != RETRO_HW_CONTEXT_NONE;

   gfx_ctx = video_context_driver_init_first(gl,
         settings->arrays.video_context_driver,
         api, major, minor, gl->use_shared_context, &ctx_data);

   if (ctx_data)
      gl->ctx_data = ctx_data;

   /* Need to force here since video_context_driver_init also checks for global option. */
   if (gfx_ctx->bind_hw_render)
      gfx_ctx->bind_hw_render(ctx_data, gl->use_shared_context);
   return gfx_ctx;
}