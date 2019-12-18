#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;

/* Variables and functions */
 int* PicoPadInt ; 

__attribute__((used)) static u32 read_pad_3btn(int i, u32 out_bits)
{
  u32 pad = ~PicoPadInt[i]; // Get inverse of pad MXYZ SACB RLDU
  u32 value;

  if (out_bits & 0x40) // TH
    value = pad & 0x3f;                      // ?1CB RLDU
  else
    value = ((pad & 0xc0) >> 2) | (pad & 3); // ?0SA 00DU

  value |= out_bits & 0x40;
  return value;
}