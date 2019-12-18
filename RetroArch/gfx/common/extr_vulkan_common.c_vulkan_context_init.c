#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct retro_hw_render_context_negotiation_interface_vulkan {scalar_t__ interface_type; scalar_t__ interface_version; TYPE_5__* (* get_application_info ) () ;} ;
struct TYPE_14__ {int /*<<< orphan*/ * instance; int /*<<< orphan*/  debug_callback; } ;
struct TYPE_15__ {TYPE_1__ context; } ;
typedef  TYPE_2__ gfx_ctx_vulkan_data_t ;
typedef  enum vulkan_wsi_type { ____Placeholder_vulkan_wsi_type } vulkan_wsi_type ;
typedef  scalar_t__ VkResult ;
struct TYPE_16__ {unsigned int enabledExtensionCount; char const** ppEnabledExtensionNames; char const** ppEnabledLayerNames; TYPE_5__* pApplicationInfo; int /*<<< orphan*/  enabledLayerCount; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ VkInstanceCreateInfo ;
struct TYPE_17__ {int flags; int /*<<< orphan*/  pfnCallback; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ VkDebugReportCallbackCreateInfoEXT ;
struct TYPE_18__ {void* apiVersion; scalar_t__ engineVersion; void* pEngineName; scalar_t__ applicationVersion; void* pApplicationName; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ VkApplicationInfo ;
typedef  scalar_t__ PFN_vkGetInstanceProcAddr ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  MSG_PROGRAM ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 scalar_t__ RETRO_HW_RENDER_CONTEXT_NEGOTIATION_INTERFACE_VULKAN ; 
 scalar_t__ RETRO_HW_RENDER_CONTEXT_NEGOTIATION_INTERFACE_VULKAN_VERSION ; 
 int VK_DEBUG_REPORT_ERROR_BIT_EXT ; 
 int VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT ; 
 int VK_DEBUG_REPORT_WARNING_BIT_EXT ; 
 scalar_t__ VK_ERROR_INCOMPATIBLE_DRIVER ; 
 void* VK_MAKE_VERSION (int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_APPLICATION_INFO ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO ; 
 scalar_t__ VK_SUCCESS ; 
 int /*<<< orphan*/  VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_EXTENSION_SYMBOL (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
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
 int /*<<< orphan*/ * cached_instance_vk ; 
 scalar_t__ dylib_load (char*) ; 
 scalar_t__ dylib_proc (scalar_t__,char*) ; 
 void* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 TYPE_5__* stub1 () ; 
 scalar_t__ video_driver_get_context_negotiation_interface () ; 
 int /*<<< orphan*/  vkCreateDebugReportCallbackEXT (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vkCreateInstance (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vkDebugReportMessageEXT (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyDebugReportCallbackEXT (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_debug_cb ; 
 int vulkan_find_instance_extensions (char const**,unsigned int) ; 
 scalar_t__ vulkan_library ; 
 int /*<<< orphan*/  vulkan_load_instance_symbols (TYPE_2__*) ; 
 int /*<<< orphan*/  vulkan_symbol_wrapper_init (scalar_t__) ; 
 int /*<<< orphan*/  vulkan_symbol_wrapper_load_global_symbols () ; 

bool vulkan_context_init(gfx_ctx_vulkan_data_t *vk,
      enum vulkan_wsi_type type)
{
   unsigned i;
   VkResult res;
   PFN_vkGetInstanceProcAddr GetInstanceProcAddr;
   VkInstanceCreateInfo info          = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
   VkApplicationInfo app              = { VK_STRUCTURE_TYPE_APPLICATION_INFO };

   const char *instance_extensions[4];
   unsigned ext_count = 0;

#ifdef VULKAN_DEBUG
   instance_extensions[ext_count++] = "VK_EXT_debug_report";
   static const char *instance_layers[] = { "VK_LAYER_LUNARG_standard_validation" };
#endif

   bool use_instance_ext;
   struct retro_hw_render_context_negotiation_interface_vulkan *iface =
      (struct retro_hw_render_context_negotiation_interface_vulkan*)video_driver_get_context_negotiation_interface();

   if (iface && iface->interface_type != RETRO_HW_RENDER_CONTEXT_NEGOTIATION_INTERFACE_VULKAN)
   {
      RARCH_WARN("[Vulkan]: Got HW context negotiation interface, but it's the wrong API.\n");
      iface = NULL;
   }

   if (iface && iface->interface_version != RETRO_HW_RENDER_CONTEXT_NEGOTIATION_INTERFACE_VULKAN_VERSION)
   {
      RARCH_WARN("[Vulkan]: Got HW context negotiation interface, but it's the wrong interface version.\n");
      iface = NULL;
   }

   instance_extensions[ext_count++] = "VK_KHR_surface";

   switch (type)
   {
      case VULKAN_WSI_WAYLAND:
         instance_extensions[ext_count++] = "VK_KHR_wayland_surface";
         break;
      case VULKAN_WSI_ANDROID:
         instance_extensions[ext_count++] = "VK_KHR_android_surface";
         break;
      case VULKAN_WSI_WIN32:
         instance_extensions[ext_count++] = "VK_KHR_win32_surface";
         break;
      case VULKAN_WSI_XLIB:
         instance_extensions[ext_count++] = "VK_KHR_xlib_surface";
         break;
      case VULKAN_WSI_XCB:
         instance_extensions[ext_count++] = "VK_KHR_xcb_surface";
         break;
      case VULKAN_WSI_MIR:
         instance_extensions[ext_count++] = "VK_KHR_mir_surface";
         break;
      case VULKAN_WSI_DISPLAY:
         instance_extensions[ext_count++] = "VK_KHR_display";
         break;
      case VULKAN_WSI_MVK_MACOS:
         instance_extensions[ext_count++] = "VK_MVK_macos_surface";
         break;
      case VULKAN_WSI_MVK_IOS:
         instance_extensions[ext_count++] = "VK_MVK_ios_surface";
         break;
      case VULKAN_WSI_NONE:
      default:
         break;
   }

   if (!vulkan_library)
   {
#ifdef _WIN32
      vulkan_library = dylib_load("vulkan-1.dll");
#elif __APPLE__
      vulkan_library = dylib_load("libMoltenVK.dylib");
#else
      vulkan_library = dylib_load("libvulkan.so");
      if (!vulkan_library)
      {
         vulkan_library = dylib_load("libvulkan.so.1");
      }
#endif
   }

   if (!vulkan_library)
   {
      RARCH_ERR("[Vulkan]: Failed to open Vulkan loader.\n");
      return false;
   }

   RARCH_LOG("Vulkan dynamic library loaded.\n");

   GetInstanceProcAddr =
      (PFN_vkGetInstanceProcAddr)dylib_proc(vulkan_library, "vkGetInstanceProcAddr");

   if (!GetInstanceProcAddr)
   {
      RARCH_ERR("[Vulkan]: Failed to load vkGetInstanceProcAddr symbol, broken loader?\n");
      return false;
   }

   vulkan_symbol_wrapper_init(GetInstanceProcAddr);

   if (!vulkan_symbol_wrapper_load_global_symbols())
   {
      RARCH_ERR("[Vulkan]: Failed to load global Vulkan symbols, broken loader?\n");
      return false;
   }

   use_instance_ext = vulkan_find_instance_extensions(instance_extensions, ext_count);

   app.pApplicationName              = msg_hash_to_str(MSG_PROGRAM);
   app.applicationVersion            = 0;
   app.pEngineName                   = msg_hash_to_str(MSG_PROGRAM);
   app.engineVersion                 = 0;
   app.apiVersion                    = VK_MAKE_VERSION(1, 0, 18);

   info.pApplicationInfo             = &app;
   info.enabledExtensionCount        = use_instance_ext ? ext_count : 0;
   info.ppEnabledExtensionNames      = use_instance_ext ? instance_extensions : NULL;
#ifdef VULKAN_DEBUG
   info.enabledLayerCount            = ARRAY_SIZE(instance_layers);
   info.ppEnabledLayerNames          = instance_layers;
#endif

   if (iface && iface->get_application_info)
   {
      info.pApplicationInfo = iface->get_application_info();
      if (info.pApplicationInfo->pApplicationName)
      {
         RARCH_LOG("[Vulkan]: App: %s (version %u)\n",
               info.pApplicationInfo->pApplicationName,
               info.pApplicationInfo->applicationVersion);
      }

      if (info.pApplicationInfo->pEngineName)
      {
         RARCH_LOG("[Vulkan]: Engine: %s (version %u)\n",
               info.pApplicationInfo->pEngineName,
               info.pApplicationInfo->engineVersion);
      }
   }

   if (cached_instance_vk)
   {
      vk->context.instance           = cached_instance_vk;
      cached_instance_vk             = NULL;
      res                            = VK_SUCCESS;
   }
   else
      res = vkCreateInstance(&info, NULL, &vk->context.instance);

#ifdef VULKAN_DEBUG
   VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_EXTENSION_SYMBOL(vk->context.instance,
         vkCreateDebugReportCallbackEXT);
   VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_EXTENSION_SYMBOL(vk->context.instance,
         vkDebugReportMessageEXT);
   VULKAN_SYMBOL_WRAPPER_LOAD_INSTANCE_EXTENSION_SYMBOL(vk->context.instance,
         vkDestroyDebugReportCallbackEXT);

   {
      VkDebugReportCallbackCreateInfoEXT info =
      { VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT };
      info.flags =
         VK_DEBUG_REPORT_ERROR_BIT_EXT |
         VK_DEBUG_REPORT_WARNING_BIT_EXT |
         VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
      info.pfnCallback = vulkan_debug_cb;

      if (vk->context.instance)
         vkCreateDebugReportCallbackEXT(vk->context.instance, &info, NULL,
               &vk->context.debug_callback);
   }
   RARCH_LOG("[Vulkan]: Enabling Vulkan debug layers.\n");
#endif

   /* Try different API versions if driver has compatible
    * but slightly different VK_API_VERSION. */
   for (i = 1; i < 4 && res == VK_ERROR_INCOMPATIBLE_DRIVER; i++)
   {
      info.pApplicationInfo = &app;
      app.apiVersion = VK_MAKE_VERSION(1, 0, i);
      res = vkCreateInstance(&info, NULL, &vk->context.instance);
   }

   if (res != VK_SUCCESS)
   {
      RARCH_ERR("Failed to create Vulkan instance (%d).\n", res);
      return false;
   }

   if (!vulkan_load_instance_symbols(vk))
   {
      RARCH_ERR("[Vulkan]: Failed to load instance symbols.\n");
      return false;
   }

   return true;
}