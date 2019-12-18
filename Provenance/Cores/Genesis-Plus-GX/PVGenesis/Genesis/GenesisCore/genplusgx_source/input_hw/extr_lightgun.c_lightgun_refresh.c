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
struct TYPE_5__ {int h; } ;
struct TYPE_8__ {TYPE_1__ viewport; } ;
struct TYPE_7__ {int** analog; int y_offset; scalar_t__* system; int x_offset; } ;
struct TYPE_6__ {int Port; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_MCD ; 
 scalar_t__ SYSTEM_MENACER ; 
 TYPE_4__ bitmap ; 
 int* hc_256 ; 
 int* hc_320 ; 
 int hvc_latch ; 
 TYPE_3__ input ; 
 int* io_reg ; 
 TYPE_2__ lightgun ; 
 int /*<<< orphan*/  m68k_update_irq (int) ; 
 int* reg ; 
 scalar_t__ system_hw ; 
 int v_counter ; 

void lightgun_refresh(int port)
{
  /* Check that lightgun is enabled */
  if (port == lightgun.Port)
  {
    /* screen Y position */
    int y = input.analog[port][1] + input.y_offset;

    /* check if active line falls within current gun Y position */
    if ((y == v_counter) && (y < bitmap.viewport.h))
    {
      /* HL enabled ? */
      if (io_reg[5] & 0x80)
      {
        /* screen X position */
        int x = input.analog[port][0];

        /* Sega Menacer specific */
        if (input.system[1] == SYSTEM_MENACER)
        {
          /* raw position is scaled up by games */
          if (system_hw == SYSTEM_MCD)
          {
            x = (x * 304) / 320;
          }
          else
          {
            x = (x * 289) / 320;
          }
        }

        /* External Interrupt enabled ? */
        if (reg[11] & 0x08) 
        {
          m68k_update_irq(2);
        }

        /* HVC latch enabled ? */
        if (reg[0] & 0x02)
        {
          /* line accurate V-Counter value */
          hvc_latch = 0x10000 | (y << 8);
        }
        else
        {
          /* HACK: force HVC latch even when disabled (a few games does not lock HV Counter but instead applies larger offset value) */
          hvc_latch = 0x20000 | (y << 8);
        }

        /* pixel accurate H-Counter value */
        if (reg[12] & 1) 
        {
          hvc_latch |= hc_320[((x / 2) + input.x_offset) % 210];
        }
        else
        {
          hvc_latch |= hc_256[((x / 2) + input.x_offset) % 171];
        }
      }
    }
    else if (hvc_latch & 0x20000)
    {
      /* HVC should be free-running on other lines when latch is disabled (fixes "Gunfight - 3 in 1" randomization) */
      hvc_latch = 0;
    }
  }
}