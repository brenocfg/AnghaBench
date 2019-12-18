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
typedef  int uint32_t ;
struct TYPE_3__ {int* publicKeys; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int GLFW_KEY_UNKNOWN ; 
 TYPE_2__ _glfw ; 

__attribute__((used)) static int toGLFWKeyCode(uint32_t key)
{
    if (key < sizeof(_glfw.wl.publicKeys) / sizeof(_glfw.wl.publicKeys[0]))
        return _glfw.wl.publicKeys[key];

    return GLFW_KEY_UNKNOWN;
}