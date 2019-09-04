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
typedef  int uint8_t ;
typedef  int int16_t ;

/* Variables and functions */
 int QUANT_MASK ; 
 int SEG_MASK ; 
 int SEG_SHIFT ; 
 int SIGN_BIT ; 

__attribute__((used)) static int16_t alaw2linear(uint8_t a_val)
{
  int16_t t, seg;

  a_val ^= 0x55;
  t = (a_val & QUANT_MASK) << 4;
  seg = ((int16_t) a_val & SEG_MASK) >> SEG_SHIFT;
  switch (seg)
  {
  case 0:
    t += 8;
    break;
  case 1:
    t += 0x108;
    break;
  default:
    t += 0x108;
    t <<= seg - 1;
  }
  return (a_val & SIGN_BIT) ? t : -t;
}