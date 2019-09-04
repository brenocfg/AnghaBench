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
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
#define  GLFW_ARROW_CURSOR 133 
#define  GLFW_CROSSHAIR_CURSOR 132 
#define  GLFW_HAND_CURSOR 131 
#define  GLFW_HRESIZE_CURSOR 130 
#define  GLFW_IBEAM_CURSOR 129 
#define  GLFW_VRESIZE_CURSOR 128 
 int /*<<< orphan*/ * IDC_ARROW ; 
 int /*<<< orphan*/ * IDC_CROSS ; 
 int /*<<< orphan*/ * IDC_HAND ; 
 int /*<<< orphan*/ * IDC_IBEAM ; 
 int /*<<< orphan*/ * IDC_SIZENS ; 
 int /*<<< orphan*/ * IDC_SIZEWE ; 

__attribute__((used)) static LPWSTR translateCursorShape(int shape)
{
    switch (shape)
    {
        case GLFW_ARROW_CURSOR:
            return IDC_ARROW;
        case GLFW_IBEAM_CURSOR:
            return IDC_IBEAM;
        case GLFW_CROSSHAIR_CURSOR:
            return IDC_CROSS;
        case GLFW_HAND_CURSOR:
            return IDC_HAND;
        case GLFW_HRESIZE_CURSOR:
            return IDC_SIZEWE;
        case GLFW_VRESIZE_CURSOR:
            return IDC_SIZENS;
    }

    return NULL;
}