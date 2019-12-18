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

/* Variables and functions */
 int sr_get_hex_digit (int) ; 

void
sr_get_hex_byte (char *byt)
{
  int val;

  val = sr_get_hex_digit (1) << 4;
  val |= sr_get_hex_digit (0);
  *byt = val;
}