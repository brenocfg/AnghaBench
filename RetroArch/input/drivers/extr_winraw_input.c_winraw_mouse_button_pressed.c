#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int btn_l; int btn_r; int btn_m; int btn_b4; int btn_b5; int whl_u; int whl_d; } ;
typedef  TYPE_2__ winraw_mouse_t ;
struct TYPE_9__ {TYPE_2__* mice; } ;
typedef  TYPE_3__ winraw_input_t ;
struct TYPE_7__ {unsigned int* input_mouse_index; } ;
struct TYPE_10__ {TYPE_1__ uints; } ;
typedef  TYPE_4__ settings_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 134 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 133 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 132 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 131 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 130 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 129 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 128 
 TYPE_4__* config_get_ptr () ; 
 unsigned int g_mouse_cnt ; 

__attribute__((used)) static bool winraw_mouse_button_pressed(
      winraw_input_t *wr, unsigned port, unsigned key)
{
	unsigned i;
	winraw_mouse_t *mouse = NULL;
	settings_t *settings  = config_get_ptr();

	if (port >= MAX_USERS)
		return false;

	for (i = 0; i < g_mouse_cnt; ++i)
	{
		if (i == settings->uints.input_mouse_index[port])
		{
			mouse = &wr->mice[i];
			break;
		}
	}

	if (!mouse)
		return false;

	switch ( key )
	{

	case RETRO_DEVICE_ID_MOUSE_LEFT:
		return mouse->btn_l;
	case RETRO_DEVICE_ID_MOUSE_RIGHT:
		return mouse->btn_r;
	case RETRO_DEVICE_ID_MOUSE_MIDDLE:
		return mouse->btn_m;
	case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
		return mouse->btn_b4;
	case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
		return mouse->btn_b5;
	case RETRO_DEVICE_ID_MOUSE_WHEELUP:
		return mouse->whl_u;
	case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
		return mouse->whl_d;
	}

	return false;
}