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
struct TYPE_3__ {int* pan; } ;
struct TYPE_4__ {TYPE_1__ OPN; } ;

/* Variables and functions */
 unsigned char TL_BITS ; 
 int bitmask ; 
 TYPE_2__ ym2612 ; 

void YM2612Config(unsigned char dac_bits)
{
  int i;

  /* DAC precision (normally 9-bit on real hardware, implemented through simple 14-bit channel output bitmasking) */
  bitmask = ~((1 << (TL_BITS - dac_bits)) - 1);

  /* update L/R panning bitmasks */
  for (i=0; i<2*6; i++)
  {
    if (ym2612.OPN.pan[i])
    {
      ym2612.OPN.pan[i] = bitmask;
    }
  }
}