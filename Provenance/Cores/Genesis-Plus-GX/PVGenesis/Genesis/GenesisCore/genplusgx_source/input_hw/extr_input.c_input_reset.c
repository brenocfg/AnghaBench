#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* dev; scalar_t__* system; } ;

/* Variables and functions */
#define  DEVICE_ACTIVATOR 137 
#define  DEVICE_LIGHTGUN 136 
#define  DEVICE_MOUSE 135 
#define  DEVICE_PAD2B 134 
#define  DEVICE_PAD3B 133 
#define  DEVICE_PAD6B 132 
#define  DEVICE_PADDLE 131 
#define  DEVICE_SPORTSPAD 130 
#define  DEVICE_TEREBI 129 
#define  DEVICE_XE_A1P 128 
 int MAX_DEVICES ; 
 scalar_t__ SYSTEM_TEAMPLAYER ; 
 int /*<<< orphan*/  activator_reset (int) ; 
 int /*<<< orphan*/  gamepad_reset (int) ; 
 TYPE_1__ input ; 
 int /*<<< orphan*/  lightgun_reset (int) ; 
 int /*<<< orphan*/  mouse_reset (int) ; 
 int /*<<< orphan*/  paddle_reset (int) ; 
 int /*<<< orphan*/  sportspad_reset (int) ; 
 int /*<<< orphan*/  teamplayer_reset (int) ; 
 int /*<<< orphan*/  terebi_oekaki_reset () ; 
 int /*<<< orphan*/  xe_a1p_reset (int) ; 

void input_reset(void)
{
  /* Reset input devices */
  int i;
  for (i=0; i<MAX_DEVICES; i++)
  {
    switch (input.dev[i])
    {
      case DEVICE_PAD2B:
      case DEVICE_PAD3B:
      case DEVICE_PAD6B:
      {
        gamepad_reset(i);
        break;
      }

      case DEVICE_LIGHTGUN:
      {
        lightgun_reset(i);
        break;
      }

      case DEVICE_MOUSE:
      {
        mouse_reset(i);
        break;
      }

      case DEVICE_ACTIVATOR:
      {
        activator_reset(i >> 2);
        break;
      }

      case DEVICE_XE_A1P:
      {
        xe_a1p_reset(i);
        break;
      }

      case DEVICE_PADDLE:
      {
        paddle_reset(i);
        break;
      }

      case DEVICE_SPORTSPAD:
      {
        sportspad_reset(i);
        break;
      }

      case DEVICE_TEREBI:
      {
        terebi_oekaki_reset();
        break;
      }

      default:
      {
        break;
      }
    }
  }

  /* Team Player */
  for (i=0; i<2; i++)
  {
    if (input.system[i] == SYSTEM_TEAMPLAYER)
    {
      teamplayer_reset(i);
    }
  }
}