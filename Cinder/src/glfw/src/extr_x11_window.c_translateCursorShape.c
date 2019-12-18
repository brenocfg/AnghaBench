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
 int XC_crosshair ; 
 int XC_hand1 ; 
 int XC_left_ptr ; 
 int XC_sb_h_double_arrow ; 
 int XC_sb_v_double_arrow ; 
 int XC_xterm ; 

__attribute__((used)) static int translateCursorShape(int shape)
{
    switch (shape)
    {
        case GLFW_ARROW_CURSOR:
            return XC_left_ptr;
        case GLFW_IBEAM_CURSOR:
            return XC_xterm;
        case GLFW_CROSSHAIR_CURSOR:
            return XC_crosshair;
        case GLFW_HAND_CURSOR:
            return XC_hand1;
        case GLFW_HRESIZE_CURSOR:
            return XC_sb_h_double_arrow;
        case GLFW_VRESIZE_CURSOR:
            return XC_sb_v_double_arrow;
    }

    return 0;
}