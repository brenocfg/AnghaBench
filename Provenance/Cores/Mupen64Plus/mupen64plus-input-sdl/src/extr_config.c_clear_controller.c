#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double* mouse_sens; int* axis_deadzone; int* axis_peak; TYPE_3__* axis; TYPE_2__* button; TYPE_1__* control; int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int button_a; int button_b; int axis_a; int axis_dir_a; int axis_b; int axis_dir_b; int hat; int hat_pos_a; int hat_pos_b; void* key_b; void* key_a; } ;
struct TYPE_6__ {int button; int axis; int axis_deadzone; int hat; int hat_pos; int mouse; void* key; } ;
struct TYPE_5__ {int /*<<< orphan*/  Plugin; scalar_t__ RawData; scalar_t__ Present; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NO_JOYSTICK ; 
 int /*<<< orphan*/  PLUGIN_NONE ; 
 void* SDL_SCANCODE_UNKNOWN ; 
 TYPE_4__* controller ; 

__attribute__((used)) static void clear_controller(int iCtrlIdx)
{
    int b;

    controller[iCtrlIdx].device = DEVICE_NO_JOYSTICK;
    controller[iCtrlIdx].control->Present = 0;
    controller[iCtrlIdx].control->RawData = 0;
    controller[iCtrlIdx].control->Plugin = PLUGIN_NONE;
    for( b = 0; b < 16; b++ )
    {
        controller[iCtrlIdx].button[b].button = -1;
        controller[iCtrlIdx].button[b].key = SDL_SCANCODE_UNKNOWN;
        controller[iCtrlIdx].button[b].axis = -1;
        controller[iCtrlIdx].button[b].axis_deadzone = -1;
        controller[iCtrlIdx].button[b].hat = -1;
        controller[iCtrlIdx].button[b].hat_pos = -1;
        controller[iCtrlIdx].button[b].mouse = -1;
    }
    for( b = 0; b < 2; b++ )
    {
        controller[iCtrlIdx].mouse_sens[b] = 2.0;
        controller[iCtrlIdx].axis_deadzone[b] = 4096;
        controller[iCtrlIdx].axis_peak[b] = 32768;
        controller[iCtrlIdx].axis[b].button_a = controller[iCtrlIdx].axis[b].button_b = -1;
        controller[iCtrlIdx].axis[b].key_a = controller[iCtrlIdx].axis[b].key_b = SDL_SCANCODE_UNKNOWN;
        controller[iCtrlIdx].axis[b].axis_a = -1;
        controller[iCtrlIdx].axis[b].axis_dir_a = 1;
        controller[iCtrlIdx].axis[b].axis_b = -1;
        controller[iCtrlIdx].axis[b].axis_dir_b = 1;
        controller[iCtrlIdx].axis[b].hat = -1;
        controller[iCtrlIdx].axis[b].hat_pos_a = -1;
        controller[iCtrlIdx].axis[b].hat_pos_b = -1;
    }
}