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
 int /*<<< orphan*/  gamepad_write (int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

void gamepad_1_write(unsigned char data, unsigned char mask)
{
  gamepad_write(0, data, mask);
}