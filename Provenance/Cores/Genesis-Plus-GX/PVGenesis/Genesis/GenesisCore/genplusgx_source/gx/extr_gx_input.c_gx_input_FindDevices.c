#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {TYPE_1__* input; } ;
struct TYPE_5__ {scalar_t__* dev; } ;
struct TYPE_4__ {int device; int port; } ;

/* Variables and functions */
 int MAX_DEVICES ; 
 scalar_t__ NO_DEVICE ; 
 int PAD_ScanPads () ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int /*<<< orphan*/  WPAD_Probe (int,int*) ; 
 TYPE_3__ config ; 
 TYPE_2__ input ; 

int gx_input_FindDevices(void)
{
  int i;
#ifdef HW_RVL
  u32 wpad;
#endif
  int found = 0;
  int player = 0;

  VIDEO_WaitVSync();
  u32 pad = PAD_ScanPads();

  for (i=0; i<MAX_DEVICES; i++)
  {
    /* check emulated peripheral */
    if (input.dev[i] != NO_DEVICE)
    {
      /* test input device */
      switch (config.input[player].device)
      {
        case 0: /* Gamecube Controller */
        {
          if (pad & (1 << config.input[player].port))
          {
            found++;
          }
          break;
        }

 #ifdef HW_RVL
        case 1:  /* Wiimote */
        {
          wpad = 255;
          WPAD_Probe(config.input[player].port, &wpad);
          if (wpad != 255)
          {
            found++;
          }
          break;
        }

        case 2: /* Expansion Controller */
        case 3:
        {
          wpad = 255;
          WPAD_Probe(config.input[player].port, &wpad);
          if (wpad == (config.input[player].device - 1))
          {
            found++;
          }
          break;
        }
 #endif

        default:
        {
          break;
        }
      }

      /* next configured player */
      player ++;
    }
  }

  /* return number of connected devices */
  return found;
}