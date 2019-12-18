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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT32_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_ADAPTIVE_VSYNC ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_GL_CORE_CONTEXT ; 
#define  GFX_CTX_NONE 129 
#define  GFX_CTX_OPENGL_API 128 
 int wgl_adaptive_vsync ; 
 int win32_api ; 
 int win32_core_hw_context_enable ; 

__attribute__((used)) static void gfx_ctx_wgl_set_flags(void *data, uint32_t flags)
{
   switch (win32_api)
   {
      case GFX_CTX_OPENGL_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         if (BIT32_GET(flags, GFX_CTX_FLAGS_ADAPTIVE_VSYNC))
            wgl_adaptive_vsync = true;

         if (BIT32_GET(flags, GFX_CTX_FLAGS_GL_CORE_CONTEXT))
            win32_core_hw_context_enable = true;
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

}