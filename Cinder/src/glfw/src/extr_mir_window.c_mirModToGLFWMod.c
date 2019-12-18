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
typedef  int uint32_t ;

/* Variables and functions */
 int GLFW_MOD_ALT ; 
 int GLFW_MOD_CONTROL ; 
 int GLFW_MOD_SHIFT ; 
 int GLFW_MOD_SUPER ; 
 int mir_input_event_modifier_alt ; 
 int mir_input_event_modifier_ctrl ; 
 int mir_input_event_modifier_meta ; 
 int mir_input_event_modifier_shift ; 

__attribute__((used)) static int mirModToGLFWMod(uint32_t mods)
{
    int publicMods = 0x0;

    if (mods & mir_input_event_modifier_alt)
        publicMods |= GLFW_MOD_ALT;
    else if (mods & mir_input_event_modifier_shift)
        publicMods |= GLFW_MOD_SHIFT;
    else if (mods & mir_input_event_modifier_ctrl)
        publicMods |= GLFW_MOD_CONTROL;
    else if (mods & mir_input_event_modifier_meta)
        publicMods |= GLFW_MOD_SUPER;

    return publicMods;
}