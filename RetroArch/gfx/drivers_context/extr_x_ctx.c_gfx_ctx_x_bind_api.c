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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ *) ; 
#define  GFX_CTX_NONE 131 
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int g_major ; 
 unsigned int g_minor ; 
 char* glXQueryExtensionsString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 int x_api ; 

__attribute__((used)) static bool gfx_ctx_x_bind_api(void *data, enum gfx_ctx_api api,
      unsigned major, unsigned minor)
{
   (void)data;

   g_major = major;
   g_minor = minor;
   x_api   = api;

   switch (api)
   {
      case GFX_CTX_OPENGL_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         return true;
#else
         break;
#endif
      case GFX_CTX_OPENGL_ES_API:
#ifdef HAVE_OPENGLES2
         {
            Display     *dpy = XOpenDisplay(NULL);
            const char *exts = glXQueryExtensionsString(dpy, DefaultScreen(dpy));
            bool ret         = exts && strstr(exts,
                  "GLX_EXT_create_context_es2_profile");
            XCloseDisplay(dpy);
            if (ret && g_major < 3)
            {
               g_major = 2; /* ES 2.0. */
               g_minor = 0;
            }
            return ret;
         }
#else
         break;
#endif
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         return true;
#else
         break;
#endif
      case GFX_CTX_NONE:
      default:
         break;
   }

   return false;
}