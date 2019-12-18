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

/* Variables and functions */
#define  GLFW_API_UNAVAILABLE 136 
#define  GLFW_FORMAT_UNAVAILABLE 135 
#define  GLFW_INVALID_ENUM 134 
#define  GLFW_INVALID_VALUE 133 
#define  GLFW_NOT_INITIALIZED 132 
#define  GLFW_NO_CURRENT_CONTEXT 131 
#define  GLFW_OUT_OF_MEMORY 130 
#define  GLFW_PLATFORM_ERROR 129 
#define  GLFW_VERSION_UNAVAILABLE 128 

__attribute__((used)) static const char* getErrorString(int error)
{
    switch (error)
    {
        case GLFW_NOT_INITIALIZED:
            return "The GLFW library is not initialized";
        case GLFW_NO_CURRENT_CONTEXT:
            return "There is no current context";
        case GLFW_INVALID_ENUM:
            return "Invalid argument for enum parameter";
        case GLFW_INVALID_VALUE:
            return "Invalid value for parameter";
        case GLFW_OUT_OF_MEMORY:
            return "Out of memory";
        case GLFW_API_UNAVAILABLE:
            return "The requested client API is unavailable";
        case GLFW_VERSION_UNAVAILABLE:
            return "The requested client API version is unavailable";
        case GLFW_PLATFORM_ERROR:
            return "A platform-specific error occurred";
        case GLFW_FORMAT_UNAVAILABLE:
            return "The requested format is unavailable";
    }

    return "ERROR: UNKNOWN ERROR TOKEN PASSED TO glfwErrorString";
}