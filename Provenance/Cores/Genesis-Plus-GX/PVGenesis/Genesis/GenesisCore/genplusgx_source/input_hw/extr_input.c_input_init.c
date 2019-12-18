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
struct TYPE_8__ {int special; } ;
struct TYPE_7__ {TYPE_1__* input; } ;
struct TYPE_6__ {int* system; void** dev; scalar_t__* pad; } ;
struct TYPE_5__ {void* padtype; } ;

/* Variables and functions */
 void* DEVICE_ACTIVATOR ; 
 void* DEVICE_LIGHTGUN ; 
 void* DEVICE_MOUSE ; 
 void* DEVICE_PAD2B ; 
 void* DEVICE_PADDLE ; 
 void* DEVICE_PICO ; 
 void* DEVICE_SPORTSPAD ; 
 void* DEVICE_TEREBI ; 
 void* DEVICE_XE_A1P ; 
 int HW_J_CART ; 
 int HW_TEREBI_OEKAKI ; 
 int MAX_DEVICES ; 
 int MAX_INPUTS ; 
 void* NO_DEVICE ; 
#define  SYSTEM_ACTIVATOR 139 
#define  SYSTEM_JUSTIFIER 138 
#define  SYSTEM_LIGHTPHASER 137 
#define  SYSTEM_MD_GAMEPAD 136 
#define  SYSTEM_MENACER 135 
#define  SYSTEM_MOUSE 134 
#define  SYSTEM_MS_GAMEPAD 133 
#define  SYSTEM_PADDLE 132 
 scalar_t__ SYSTEM_PICO ; 
#define  SYSTEM_SPORTSPAD 131 
#define  SYSTEM_TEAMPLAYER 130 
#define  SYSTEM_WAYPLAY 129 
#define  SYSTEM_XE_A1P 128 
 TYPE_4__ cart ; 
 TYPE_3__ config ; 
 TYPE_2__ input ; 
 scalar_t__ system_hw ; 
 int /*<<< orphan*/  teamplayer_init (int) ; 

void input_init(void)
{
  int i;
  int player = 0;

  for (i=0; i<MAX_DEVICES; i++)
  {
    input.dev[i] = NO_DEVICE;
    input.pad[i] = 0;
  }

  /* PICO tablet */
  if (system_hw == SYSTEM_PICO)
  {
    input.dev[0] = DEVICE_PICO;
    return;
  }

  /* Terebi Oekaki tablet */
  if (cart.special & HW_TEREBI_OEKAKI)
  {
    input.dev[0] = DEVICE_TEREBI;
    return;
  }

  switch (input.system[0])
  {
    case SYSTEM_MS_GAMEPAD:
    {
      input.dev[0] = DEVICE_PAD2B;
      player++;
      break;
    }

    case SYSTEM_MD_GAMEPAD:
    {
      input.dev[0] = config.input[player].padtype;
      player++;
      break;
    }

    case SYSTEM_MOUSE:
    {
      input.dev[0] = DEVICE_MOUSE;
      player++;
      break;
    }

    case SYSTEM_ACTIVATOR:
    {
      input.dev[0] = DEVICE_ACTIVATOR;
      player++;
      break;
    }

    case SYSTEM_XE_A1P:
    {
      input.dev[0] = DEVICE_XE_A1P;
      player++;
      break;
    }

    case SYSTEM_WAYPLAY:
    {
      for (i=0; i< 4; i++)
      {
        if (player < MAX_INPUTS)
        {
          input.dev[i] = config.input[player].padtype;
          player++;
        }
      }
      break;
    }

    case SYSTEM_TEAMPLAYER:
    {
      for (i=0; i<4; i++)
      {
        if (player < MAX_INPUTS)
        {
          input.dev[i] = config.input[player].padtype;
          player++;
        }
      }
      teamplayer_init(0);
      break;
    }

    case SYSTEM_LIGHTPHASER:
    {
      input.dev[0] = DEVICE_LIGHTGUN;
      player++;
      break;
    }

    case SYSTEM_PADDLE:
    {
      input.dev[0] = DEVICE_PADDLE;
      player++;
      break;
    }

    case SYSTEM_SPORTSPAD:
    {
      input.dev[0] = DEVICE_SPORTSPAD;
      player++;
      break;
    }
  }

  if (player == MAX_INPUTS)
  {
    return;
  }

  switch (input.system[1])
  {
    case SYSTEM_MS_GAMEPAD:
    {
      input.dev[4] = DEVICE_PAD2B;
      player++;
      break;
    }

    case SYSTEM_MD_GAMEPAD:
    {
      input.dev[4] = config.input[player].padtype;
      player++;
      break;
    }

    case SYSTEM_MOUSE:
    {
      input.dev[4] = DEVICE_MOUSE;
      player++;
      break;
    }

    case SYSTEM_ACTIVATOR:
    {
      input.dev[4] = DEVICE_ACTIVATOR;
      player++;
      break;
    }

    case SYSTEM_XE_A1P:
    {
      input.dev[4] = DEVICE_XE_A1P;
      player++;
      break;
    }

    case SYSTEM_MENACER:
    {
      input.dev[4] = DEVICE_LIGHTGUN;
      player++;
      break;
    }

    case SYSTEM_JUSTIFIER:
    {
      for (i=4; i<6; i++)
      {
        if (player < MAX_INPUTS)
        {
          input.dev[i] = DEVICE_LIGHTGUN;
          player++;
        }
      }
      break;
    }

    case SYSTEM_TEAMPLAYER:
    {
      for (i=4; i<8; i++)
      {
        if (player < MAX_INPUTS)
        {
          input.dev[i] = config.input[player].padtype;
          player++;
        }
      }
      teamplayer_init(1);
      break;
    }

    case SYSTEM_LIGHTPHASER:
    {
      input.dev[4] = DEVICE_LIGHTGUN;
      player++;
      break;
    }

    case SYSTEM_PADDLE:
    {
      input.dev[4] = DEVICE_PADDLE;
      player++;
      break;
    }

    case SYSTEM_SPORTSPAD:
    {
      input.dev[4] = DEVICE_SPORTSPAD;
      player++;
      break;
    }
  }

  /* J-CART */
  if (cart.special & HW_J_CART)
  {
    /* two additional gamepads */
    for (i=5; i<7; i++)
    {
      if (player < MAX_INPUTS)
      {
        input.dev[i] = config.input[player].padtype;
        player ++;
      }
    }
  }
}