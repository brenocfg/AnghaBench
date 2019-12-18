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
struct TYPE_2__ {int* pad; } ;

/* Variables and functions */
 TYPE_1__ input ; 

unsigned char menacer_read(void)
{
  /* D0=??? (INPUT_B), D1=TRIGGER (INPUT_A), D2=??? (INPUT_C), D3= START (INPUT_START) (active high) */
  /* TL & TR pins always return 0 (normally set as output)  */
  /* TH always return 1 (0 on active pixel but button acquisition is always done during VBLANK) */
  unsigned data = input.pad[4] >> 4;
  return ((data & 0x09) | ((data >> 1) & 0x02) | ((data << 1) & 0x04) | 0x40);
}