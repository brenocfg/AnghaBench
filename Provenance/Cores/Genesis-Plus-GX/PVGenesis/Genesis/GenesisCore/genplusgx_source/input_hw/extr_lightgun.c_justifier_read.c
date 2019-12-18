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
struct TYPE_4__ {int* pad; } ;
struct TYPE_3__ {int State; size_t Port; } ;

/* Variables and functions */
 TYPE_2__ input ; 
 TYPE_1__ lightgun ; 

unsigned char justifier_read(void)
{
  /* Gun detection */
  if (lightgun.State & 0x40)
  {
    return 0x30;
  }

  /* Return TRIGGER (INPUT_A) & START (INPUT_START) button status in D0-D1 (active low) */
  /* TL & TR pins should always return 1 (normally set as output) */
  /* LEFT & RIGHT pins should always return 0 */
  return (((~input.pad[lightgun.Port] >> 6) & 0x03) | 0x70);
}