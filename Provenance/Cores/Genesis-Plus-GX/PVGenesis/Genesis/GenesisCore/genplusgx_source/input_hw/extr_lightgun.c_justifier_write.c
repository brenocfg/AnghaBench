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
struct TYPE_2__ {int Port; unsigned char State; } ;

/* Variables and functions */
 TYPE_1__ lightgun ; 

void justifier_write(unsigned char data, unsigned char mask)
{
  /* update bits set as output only, other bits are cleared (fixes Lethal Enforcers 2) */
  data &= mask;

  /* gun index */
  lightgun.Port = 4 + ((data >> 5) & 1);

  /* update internal state */
  lightgun.State = data;
}