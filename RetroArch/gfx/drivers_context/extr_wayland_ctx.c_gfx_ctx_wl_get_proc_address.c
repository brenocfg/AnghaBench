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
typedef  int /*<<< orphan*/ * gfx_ctx_proc_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 131 
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_OPENVG_API 128 
 int /*<<< orphan*/ * egl_get_proc_address (char const*) ; 
 int wl_api ; 

__attribute__((used)) static gfx_ctx_proc_t gfx_ctx_wl_get_proc_address(const char *symbol)
{
   switch (wl_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         return egl_get_proc_address(symbol);
#else
         break;
#endif
      case GFX_CTX_NONE:
      default:
         break;
   }

   return NULL;
}