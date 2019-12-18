#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xcb_window_t ;
typedef  int /*<<< orphan*/  surf_info ;
struct wl_surface {int dummy; } ;
struct wl_display {int dummy; } ;
struct vulkan_display_surface_info {int dummy; } ;
struct TYPE_26__ {int /*<<< orphan*/  instance; } ;
struct TYPE_27__ {scalar_t__ vk_surface; TYPE_1__ context; } ;
typedef  TYPE_2__ gfx_ctx_vulkan_data_t ;
typedef  enum vulkan_wsi_type { ____Placeholder_vulkan_wsi_type } vulkan_wsi_type ;
typedef  int /*<<< orphan*/ * Window ;
struct TYPE_28__ {void* pView; int /*<<< orphan*/  flags; int /*<<< orphan*/ * pNext; int /*<<< orphan*/  sType; void* mirSurface; void* connection; int /*<<< orphan*/ * window; int /*<<< orphan*/ * dpy; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  hinstance; struct wl_surface* surface; struct wl_display* display; } ;
typedef  TYPE_3__ VkXlibSurfaceCreateInfoKHR ;
typedef  TYPE_3__ VkXcbSurfaceCreateInfoKHR ;
typedef  TYPE_3__ VkWin32SurfaceCreateInfoKHR ;
typedef  TYPE_3__ VkWaylandSurfaceCreateInfoKHR ;
typedef  TYPE_3__ VkMirSurfaceCreateInfoKHR ;
typedef  TYPE_3__ VkMacOSSurfaceCreateInfoMVK ;
typedef  TYPE_3__ VkIOSSurfaceCreateInfoMVK ;
typedef  TYPE_3__ VkAndroidSurfaceCreateInfoKHR ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateXlibSurfaceKHR ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateXcbSurfaceKHR ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateWin32SurfaceKHR ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateWaylandSurfaceKHR ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateMirSurfaceKHR ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateMacOSSurfaceMVK ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateIOSSurfaceMVK ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  (* PFN_vkCreateAndroidSurfaceKHR ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  ANativeWindow ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned long long) ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR ; 
 int /*<<< orphan*/  VK_SUCCESS ; 
 int /*<<< orphan*/  VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*)) ; 
#define  VULKAN_WSI_ANDROID 137 
#define  VULKAN_WSI_DISPLAY 136 
#define  VULKAN_WSI_MIR 135 
#define  VULKAN_WSI_MVK_IOS 134 
#define  VULKAN_WSI_MVK_MACOS 133 
#define  VULKAN_WSI_NONE 132 
#define  VULKAN_WSI_WAYLAND 131 
#define  VULKAN_WSI_WIN32 130 
#define  VULKAN_WSI_XCB 129 
#define  VULKAN_WSI_XLIB 128 
 void* XGetXCBConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vulkan_acquire_next_image (TYPE_2__*) ; 
 int /*<<< orphan*/  vulkan_context_init_device (TYPE_2__*) ; 
 int /*<<< orphan*/  vulkan_create_display_surface (TYPE_2__*,unsigned int*,unsigned int*,struct vulkan_display_surface_info const*) ; 
 int /*<<< orphan*/  vulkan_create_swapchain (TYPE_2__*,unsigned int,unsigned int,unsigned int) ; 

bool vulkan_surface_create(gfx_ctx_vulkan_data_t *vk,
      enum vulkan_wsi_type type,
      void *display, void *surface,
      unsigned width, unsigned height,
      unsigned swap_interval)
{
   switch (type)
   {
      case VULKAN_WSI_WAYLAND:
#ifdef HAVE_WAYLAND
         {
            PFN_vkCreateWaylandSurfaceKHR create;
            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateWaylandSurfaceKHR", create))
               return false;
            VkWaylandSurfaceCreateInfoKHR surf_info;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType   = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
            surf_info.pNext   = NULL;
            surf_info.flags   = 0;
            surf_info.display = (struct wl_display*)display;
            surf_info.surface = (struct wl_surface*)surface;

            if (create(vk->context.instance,
                     &surf_info, NULL, &vk->vk_surface) != VK_SUCCESS)
               return false;
         }
#endif
         break;
      case VULKAN_WSI_ANDROID:
#ifdef ANDROID
         {
            PFN_vkCreateAndroidSurfaceKHR create;
            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateAndroidSurfaceKHR", create))
               return false;
            VkAndroidSurfaceCreateInfoKHR surf_info;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType  = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
            surf_info.flags  = 0;
            surf_info.window = (ANativeWindow*)surface;

            if (create(vk->context.instance,
                     &surf_info, NULL, &vk->vk_surface) != VK_SUCCESS)
            {
               RARCH_ERR("[Vulkan]: Failed to create Android surface.\n");
               return false;
            }
            RARCH_LOG("[Vulkan]: Created Android surface: %llu\n",
                  (unsigned long long)vk->vk_surface);
         }
#endif
         break;
      case VULKAN_WSI_WIN32:
#ifdef _WIN32
         {
            VkWin32SurfaceCreateInfoKHR surf_info;
            PFN_vkCreateWin32SurfaceKHR create;

            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateWin32SurfaceKHR", create))
               return false;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
            surf_info.flags     = 0;
            surf_info.hinstance = *(const HINSTANCE*)display;
            surf_info.hwnd      = *(const HWND*)surface;

            if (create(vk->context.instance,
                     &surf_info, NULL, &vk->vk_surface) != VK_SUCCESS)
               return false;
         }
#endif
         break;
      case VULKAN_WSI_XLIB:
#ifdef HAVE_XLIB
         {
            PFN_vkCreateXlibSurfaceKHR create;
            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateXlibSurfaceKHR", create))
               return false;
            VkXlibSurfaceCreateInfoKHR surf_info;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType  = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
            surf_info.flags  = 0;
            surf_info.dpy    = (Display*)display;
            surf_info.window = *(const Window*)surface;

            if (create(vk->context.instance,
                     &surf_info, NULL, &vk->vk_surface)
                  != VK_SUCCESS)
               return false;
         }
#endif
         break;
      case VULKAN_WSI_XCB:
#ifdef HAVE_X11
#ifdef HAVE_XCB
         {
            PFN_vkCreateXcbSurfaceKHR create;
            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateXcbSurfaceKHR", create))
               return false;
            VkXcbSurfaceCreateInfoKHR surf_info;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType      = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
            surf_info.flags      = 0;
            surf_info.connection = XGetXCBConnection((Display*)display);
            surf_info.window     = *(const xcb_window_t*)surface;

            if (create(vk->context.instance,
                     &surf_info, NULL, &vk->vk_surface)
                  != VK_SUCCESS)
               return false;
         }
#endif
#endif
         break;
      case VULKAN_WSI_MIR:
#ifdef HAVE_MIR
         {
            PFN_vkCreateMirSurfaceKHR create;
            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateMirSurfaceKHR", create))
               return false;
            VkMirSurfaceCreateInfoKHR surf_info;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType      = VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR;
            surf_info.connection = display;
            surf_info.mirSurface = surface;

            if (create(vk->context.instance,
                     &surf_info, NULL, &vk->vk_surface)
                  != VK_SUCCESS)
               return false;
         }
#endif
         break;
      case VULKAN_WSI_DISPLAY:
         {
            if (!vulkan_create_display_surface(vk,
                     &width, &height,
                     (const struct vulkan_display_surface_info*)display))
               return false;
         }
         break;
      case VULKAN_WSI_MVK_MACOS:
#ifdef HAVE_COCOA
         {
            PFN_vkCreateMacOSSurfaceMVK create;
            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateMacOSSurfaceMVK", create))
               return false;
            VkMacOSSurfaceCreateInfoMVK surf_info;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
            surf_info.pNext = NULL;
            surf_info.flags = 0;
            surf_info.pView = surface;

            if (create(vk->context.instance, &surf_info, NULL, &vk->vk_surface)
                != VK_SUCCESS)
               return false;
         }
#endif
         break;
      case VULKAN_WSI_MVK_IOS:
#ifdef HAVE_COCOATOUCH
         {
            PFN_vkCreateIOSSurfaceMVK create;
            if (!VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_SYMBOL(vk->context.instance, "vkCreateIOSSurfaceMVK", create))
               return false;
            VkIOSSurfaceCreateInfoMVK surf_info;

            memset(&surf_info, 0, sizeof(surf_info));

            surf_info.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
            surf_info.pNext = NULL;
            surf_info.flags = 0;
            surf_info.pView = surface;

            if (create(vk->context.instance, &surf_info, NULL, &vk->vk_surface)
                != VK_SUCCESS)
               return false;
         }
#endif
         break;
      case VULKAN_WSI_NONE:
      default:
         return false;
   }

   /* Must create device after surface since we need to be able to query queues to use for presentation. */
   if (!vulkan_context_init_device(vk))
      return false;

   if (!vulkan_create_swapchain(
            vk, width, height, swap_interval))
      return false;

   vulkan_acquire_next_image(vk);
   return true;
}