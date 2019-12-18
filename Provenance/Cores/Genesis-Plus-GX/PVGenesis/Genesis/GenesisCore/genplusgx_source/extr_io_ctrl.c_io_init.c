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
struct TYPE_4__ {int* system; } ;
struct TYPE_3__ {void* data_r; void* data_w; } ;

/* Variables and functions */
#define  SYSTEM_ACTIVATOR 139 
#define  SYSTEM_JUSTIFIER 138 
#define  SYSTEM_LIGHTPHASER 137 
#define  SYSTEM_MD_GAMEPAD 136 
#define  SYSTEM_MENACER 135 
#define  SYSTEM_MOUSE 134 
#define  SYSTEM_MS_GAMEPAD 133 
#define  SYSTEM_PADDLE 132 
#define  SYSTEM_SPORTSPAD 131 
#define  SYSTEM_TEAMPLAYER 130 
#define  SYSTEM_WAYPLAY 129 
#define  SYSTEM_XE_A1P 128 
 void* activator_1_read ; 
 void* activator_1_write ; 
 void* activator_2_read ; 
 void* activator_2_write ; 
 void* dummy_read ; 
 void* dummy_write ; 
 void* gamepad_1_read ; 
 void* gamepad_1_write ; 
 void* gamepad_2_read ; 
 void* gamepad_2_write ; 
 TYPE_2__ input ; 
 int /*<<< orphan*/  input_init () ; 
 void* justifier_read ; 
 void* justifier_write ; 
 void* menacer_read ; 
 void* mouse_read ; 
 void* mouse_write ; 
 void* paddle_1_read ; 
 void* paddle_1_write ; 
 void* paddle_2_read ; 
 void* paddle_2_write ; 
 void* phaser_1_read ; 
 void* phaser_2_read ; 
 TYPE_1__* port ; 
 void* sportspad_1_read ; 
 void* sportspad_1_write ; 
 void* sportspad_2_read ; 
 void* sportspad_2_write ; 
 void* teamplayer_1_read ; 
 void* teamplayer_1_write ; 
 void* teamplayer_2_read ; 
 void* teamplayer_2_write ; 
 void* wayplay_1_read ; 
 void* wayplay_1_write ; 
 void* wayplay_2_read ; 
 void* wayplay_2_write ; 
 void* xe_a1p_1_read ; 
 void* xe_a1p_1_write ; 
 void* xe_a1p_2_read ; 
 void* xe_a1p_2_write ; 

void io_init(void)
{
  /* Initialize connected peripherals */
  input_init();

  /* Initialize IO Ports handlers & connected peripherals */
  switch (input.system[0])
  {
    case SYSTEM_MS_GAMEPAD:
    {
      port[0].data_w = dummy_write;
      port[0].data_r = gamepad_1_read;
      break;
    }

    case SYSTEM_MD_GAMEPAD:
    {
      port[0].data_w = gamepad_1_write;
      port[0].data_r = gamepad_1_read;
      break;
    }

    case SYSTEM_MOUSE:
    {
      port[0].data_w = mouse_write;
      port[0].data_r = mouse_read;
      break;
    }

    case SYSTEM_ACTIVATOR:
    {
      port[0].data_w = activator_1_write;
      port[0].data_r = activator_1_read;
      break;
    }

    case SYSTEM_XE_A1P:
    {
      port[0].data_w = xe_a1p_1_write;
      port[0].data_r = xe_a1p_1_read;
      break;
    }

    case SYSTEM_WAYPLAY:
    {
      port[0].data_w = wayplay_1_write;
      port[0].data_r = wayplay_1_read;
      break;
    }

    case SYSTEM_TEAMPLAYER:
    {
      port[0].data_w = teamplayer_1_write;
      port[0].data_r = teamplayer_1_read;
      break;
    }

    case SYSTEM_LIGHTPHASER:
    {
      port[0].data_w = dummy_write;
      port[0].data_r = phaser_1_read;
      break;
    }

    case SYSTEM_PADDLE:
    {
      port[0].data_w = paddle_1_write;
      port[0].data_r = paddle_1_read;
      break;
    }

    case SYSTEM_SPORTSPAD:
    {
      port[0].data_w = sportspad_1_write;
      port[0].data_r = sportspad_1_read;
      break;
    }

    default:
    {
      port[0].data_w = dummy_write;
      port[0].data_r = dummy_read;
      break;
    }
  }

  switch (input.system[1])
  {
    case SYSTEM_MS_GAMEPAD:
    {
      port[1].data_w = dummy_write;
      port[1].data_r = gamepad_2_read;
      break;
    }

    case SYSTEM_MD_GAMEPAD:
    {
      port[1].data_w = gamepad_2_write;
      port[1].data_r = gamepad_2_read;
      break;
    }

    case SYSTEM_MOUSE:
    {
      port[1].data_w = mouse_write;
      port[1].data_r = mouse_read;
      break;
    }

    case SYSTEM_XE_A1P:
    {
      port[1].data_w = xe_a1p_2_write;
      port[1].data_r = xe_a1p_2_read;
      break;
    }

    case SYSTEM_ACTIVATOR:
    {
      port[1].data_w = activator_2_write;
      port[1].data_r = activator_2_read;
      break;
    }

    case SYSTEM_MENACER:
    {
      port[1].data_w = dummy_write;
      port[1].data_r = menacer_read;
      break;
    }

    case SYSTEM_JUSTIFIER:
    {
      port[1].data_w = justifier_write;
      port[1].data_r = justifier_read;
      break;
    }

    case SYSTEM_WAYPLAY:
    {
      port[1].data_w = wayplay_2_write;
      port[1].data_r = wayplay_2_read;
      break;
    }

    case SYSTEM_TEAMPLAYER:
    {
      port[1].data_w = teamplayer_2_write;
      port[1].data_r = teamplayer_2_read;
      break;
    }

    case SYSTEM_LIGHTPHASER:
    {
      port[1].data_w = dummy_write;
      port[1].data_r = phaser_2_read;
      break;
    }

    case SYSTEM_PADDLE:
    {
      port[1].data_w = paddle_2_write;
      port[1].data_r = paddle_2_read;
      break;
    }

    case SYSTEM_SPORTSPAD:
    {
      port[1].data_w = sportspad_2_write;
      port[1].data_r = sportspad_2_read;
      break;
    }

    default:
    {
      port[1].data_w = dummy_write;
      port[1].data_r = dummy_read;
      break;
    }
  }

  /* External Port (unconnected) */
  port[2].data_w = dummy_write;
  port[2].data_r = dummy_read;
}