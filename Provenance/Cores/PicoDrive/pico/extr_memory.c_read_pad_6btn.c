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
typedef  int u32 ;
struct TYPE_3__ {int* padTHPhase; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int* PicoPadInt ; 

__attribute__((used)) static u32 read_pad_6btn(int i, u32 out_bits)
{
  u32 pad = ~PicoPadInt[i]; // Get inverse of pad MXYZ SACB RLDU
  int phase = Pico.m.padTHPhase[i];
  u32 value;

  if (phase == 2 && !(out_bits & 0x40)) {
    value = (pad & 0xc0) >> 2;                   // ?0SA 0000
    goto out;
  }
  else if(phase == 3) {
    if (out_bits & 0x40)
      return (pad & 0x30) | ((pad >> 8) & 0xf);  // ?1CB MXYZ
    else
      return ((pad & 0xc0) >> 2) | 0x0f;         // ?0SA 1111
    goto out;
  }

  if (out_bits & 0x40) // TH
    value = pad & 0x3f;                          // ?1CB RLDU
  else
    value = ((pad & 0xc0) >> 2) | (pad & 3);     // ?0SA 00DU

out:
  value |= out_bits & 0x40;
  return value;
}