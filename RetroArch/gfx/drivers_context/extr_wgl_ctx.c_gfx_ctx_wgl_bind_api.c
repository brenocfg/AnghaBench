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
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;

/* Variables and functions */
 int GFX_CTX_OPENGL_API ; 
 int GFX_CTX_VULKAN_API ; 
 int win32_api ; 
 unsigned int win32_major ; 
 unsigned int win32_minor ; 

__attribute__((used)) static bool gfx_ctx_wgl_bind_api(void *data,
      enum gfx_ctx_api api, unsigned major, unsigned minor)
{
   (void)data;

   win32_major = major;
   win32_minor = minor;
   win32_api   = api;

#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
   if (api == GFX_CTX_OPENGL_API)
      return true;
#endif
#if defined(HAVE_VULKAN)
   if (api == GFX_CTX_VULKAN_API)
      return true;
#endif

   return false;
}