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
 int /*<<< orphan*/  OSMESA_COMPAT_PROFILE ; 
 int g_osmesa_major ; 
 int g_osmesa_minor ; 
 int /*<<< orphan*/  g_osmesa_profile ; 
 int osmesa_api ; 

__attribute__((used)) static bool osmesa_ctx_bind_api(void *data,
      enum gfx_ctx_api api, unsigned major,
      unsigned minor)
{
   if (api != GFX_CTX_OPENGL_API)
      return false;

   osmesa_api       = api;
   g_osmesa_profile = OSMESA_COMPAT_PROFILE;

   if (major)
   {
      g_osmesa_major = major;
      g_osmesa_minor = minor;
   }
   else
   {
      g_osmesa_major = 2;
      g_osmesa_minor = 1;
   }

   return true;
}