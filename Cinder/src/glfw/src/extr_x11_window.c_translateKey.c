#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* publicKeys; } ;
struct TYPE_4__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int GLFW_KEY_UNKNOWN ; 
 TYPE_2__ _glfw ; 

__attribute__((used)) static int translateKey(int scancode)
{
    // Use the pre-filled LUT (see createKeyTables() in x11_init.c)
    if (scancode < 0 || scancode > 255)
        return GLFW_KEY_UNKNOWN;

    return _glfw.x11.publicKeys[scancode];
}