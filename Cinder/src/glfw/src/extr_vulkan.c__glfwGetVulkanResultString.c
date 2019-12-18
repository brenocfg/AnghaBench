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
typedef  int VkResult ;

/* Variables and functions */
#define  VK_ERROR_DEVICE_LOST 150 
#define  VK_ERROR_EXTENSION_NOT_PRESENT 149 
#define  VK_ERROR_FEATURE_NOT_PRESENT 148 
#define  VK_ERROR_FORMAT_NOT_SUPPORTED 147 
#define  VK_ERROR_INCOMPATIBLE_DISPLAY_KHR 146 
#define  VK_ERROR_INCOMPATIBLE_DRIVER 145 
#define  VK_ERROR_INITIALIZATION_FAILED 144 
#define  VK_ERROR_LAYER_NOT_PRESENT 143 
#define  VK_ERROR_MEMORY_MAP_FAILED 142 
#define  VK_ERROR_NATIVE_WINDOW_IN_USE_KHR 141 
#define  VK_ERROR_OUT_OF_DATE_KHR 140 
#define  VK_ERROR_OUT_OF_DEVICE_MEMORY 139 
#define  VK_ERROR_OUT_OF_HOST_MEMORY 138 
#define  VK_ERROR_SURFACE_LOST_KHR 137 
#define  VK_ERROR_TOO_MANY_OBJECTS 136 
#define  VK_ERROR_VALIDATION_FAILED_EXT 135 
#define  VK_EVENT_RESET 134 
#define  VK_EVENT_SET 133 
#define  VK_INCOMPLETE 132 
#define  VK_NOT_READY 131 
#define  VK_SUBOPTIMAL_KHR 130 
#define  VK_SUCCESS 129 
#define  VK_TIMEOUT 128 

const char* _glfwGetVulkanResultString(VkResult result)
{
    switch (result)
    {
        case VK_SUCCESS:
            return "Success";
        case VK_NOT_READY:
            return "A fence or query has not yet completed";
        case VK_TIMEOUT:
            return "A wait operation has not completed in the specified time";
        case VK_EVENT_SET:
            return "An event is signaled";
        case VK_EVENT_RESET:
            return "An event is unsignaled";
        case VK_INCOMPLETE:
            return "A return array was too small for the result";
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "A host memory allocation has failed";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "A device memory allocation has failed";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "Initialization of an object could not be completed for implementation-specific reasons";
        case VK_ERROR_DEVICE_LOST:
            return "The logical or physical device has been lost";
        case VK_ERROR_MEMORY_MAP_FAILED:
            return "Mapping of a memory object has failed";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "A requested layer is not present or could not be loaded";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "A requested extension is not supported";
        case VK_ERROR_FEATURE_NOT_PRESENT:
            return "A requested feature is not supported";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible";
        case VK_ERROR_TOO_MANY_OBJECTS:
            return "Too many objects of the type have already been created";
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            return "A requested format is not supported on this device";
        case VK_ERROR_SURFACE_LOST_KHR:
            return "A surface is no longer available";
        case VK_SUBOPTIMAL_KHR:
            return "A swapchain no longer matches the surface properties exactly, but can still be used";
        case VK_ERROR_OUT_OF_DATE_KHR:
            return "A surface has changed in such a way that it is no longer compatible with the swapchain";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            return "The display used by a swapchain does not use the same presentable image layout";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API";
        case VK_ERROR_VALIDATION_FAILED_EXT:
            return "A validation layer found an error";
        default:
            return "ERROR: UNKNOWN VULKAN ERROR";
    }
}