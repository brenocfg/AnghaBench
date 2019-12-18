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
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
#define  GFX_CTX_OPENGL_API 128 
 int /*<<< orphan*/  GetProcAddress (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dll_handle ; 
 int /*<<< orphan*/  wglGetProcAddress (char const*) ; 
 int win32_api ; 

__attribute__((used)) static gfx_ctx_proc_t gfx_ctx_wgl_get_proc_address(const char *symbol)
{
   switch (win32_api)
   {
      case GFX_CTX_OPENGL_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         {
            gfx_ctx_proc_t func = (gfx_ctx_proc_t)wglGetProcAddress(symbol);
            if (func)
               return func;
         }
#endif
         break;
      default:
         break;
   }

#ifdef HAVE_DYNAMIC
   return (gfx_ctx_proc_t)GetProcAddress((HINSTANCE)dll_handle, symbol);
#else
   return NULL;
#endif
}