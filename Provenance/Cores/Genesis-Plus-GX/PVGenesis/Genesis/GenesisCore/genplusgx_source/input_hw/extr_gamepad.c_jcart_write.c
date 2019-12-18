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
 int /*<<< orphan*/  gamepad_write (int,unsigned int,int) ; 

void jcart_write(unsigned int address, unsigned int data)
{
  gamepad_write(5, (data & 1) << 6, 0x40);
  gamepad_write(6, (data & 1) << 6, 0x40);
  return;
}