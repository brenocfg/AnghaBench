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
#define  GLFW_ARROW_CURSOR 133 
#define  GLFW_CROSSHAIR_CURSOR 132 
#define  GLFW_HAND_CURSOR 131 
#define  GLFW_HRESIZE_CURSOR 130 
#define  GLFW_IBEAM_CURSOR 129 
#define  GLFW_VRESIZE_CURSOR 128 
 char const* mir_arrow_cursor_name ; 
 char const* mir_caret_cursor_name ; 
 char const* mir_crosshair_cursor_name ; 
 char const* mir_horizontal_resize_cursor_name ; 
 char const* mir_open_hand_cursor_name ; 
 char const* mir_vertical_resize_cursor_name ; 

const char* getSystemCursorName(int shape)
{
    switch (shape)
    {
        case GLFW_ARROW_CURSOR:
            return mir_arrow_cursor_name;
        case GLFW_IBEAM_CURSOR:
            return mir_caret_cursor_name;
        case GLFW_CROSSHAIR_CURSOR:
            return mir_crosshair_cursor_name;
        case GLFW_HAND_CURSOR:
            return mir_open_hand_cursor_name;
        case GLFW_HRESIZE_CURSOR:
            return mir_horizontal_resize_cursor_name;
        case GLFW_VRESIZE_CURSOR:
            return mir_vertical_resize_cursor_name;
    }

    return NULL;
}