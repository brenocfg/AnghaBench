#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int right; unsigned int left; unsigned int bottom; unsigned int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
#define  GFX_CTX_NONE 130 
#define  GFX_CTX_OPENGL_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VULKAN_WSI_WIN32 ; 
 int /*<<< orphan*/  create_gl_context (int /*<<< orphan*/ ,int*) ; 
 int g_win32_inited ; 
 int /*<<< orphan*/  vulkan_surface_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int win32_api ; 
 int /*<<< orphan*/  win32_interval ; 
 int /*<<< orphan*/  win32_vk ; 

void create_graphics_context(HWND hwnd, bool *quit)
{
   switch (win32_api)
   {
      case GFX_CTX_OPENGL_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         create_gl_context(hwnd, quit);
#endif
         break;

      case GFX_CTX_VULKAN_API:
      {
#ifdef HAVE_VULKAN
         RECT rect;
         HINSTANCE instance;
         unsigned width  = 0;
         unsigned height = 0;

         GetClientRect(hwnd, &rect);

         instance = GetModuleHandle(NULL);
         width    = rect.right - rect.left;
         height   = rect.bottom - rect.top;

         if (!vulkan_surface_create(&win32_vk, VULKAN_WSI_WIN32,
                  &instance, &hwnd,
                  width, height, win32_interval))
            *quit = true;

         g_win32_inited = true;
#endif
      }
      break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}