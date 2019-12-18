#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bankshift; } ;
struct TYPE_10__ {int mask; int special; scalar_t__ rom; TYPE_1__ hw; } ;
struct TYPE_9__ {int lock_on; } ;
struct TYPE_8__ {TYPE_2__* memory_map; } ;
struct TYPE_7__ {scalar_t__ base; } ;

/* Variables and functions */
 int HW_LOCK_ON ; 
#define  TYPE_AR 130 
#define  TYPE_GG 129 
#define  TYPE_SK 128 
 int /*<<< orphan*/  areplay_reset (int) ; 
 TYPE_5__ cart ; 
 TYPE_4__ config ; 
 int /*<<< orphan*/  ggenie_reset (int) ; 
 TYPE_3__ m68k ; 
 scalar_t__ svp ; 
 int /*<<< orphan*/  svp_reset () ; 

void md_cart_reset(int hard_reset)
{
  int i;

  /* reset cartridge mapping */
  if (cart.hw.bankshift)
  {
    for (i=0x00; i<0x40; i++)
    {
      m68k.memory_map[i].base = cart.rom + ((i<<16) & cart.mask);
    }
  }
  
  /* SVP chip */
  if (svp)
  {
    svp_reset();
  }

  /* Lock-ON */
  switch (config.lock_on)
  {
    case TYPE_GG:
    {
      ggenie_reset(hard_reset);
      break;
    }

    case TYPE_AR:
    {
      areplay_reset(hard_reset);
      break;
    }

    case TYPE_SK:
    {
      if (cart.special & HW_LOCK_ON)
      {
        /* disable UPMEM chip at $300000-$3fffff */
        for (i=0x30; i<0x40; i++)
        {
          m68k.memory_map[i].base = cart.rom + ((i<<16) & cart.mask);
        }
      }
      break;
    }

    default:
    {
      break;
    }
  }
}