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
 int /*<<< orphan*/  SONY_PIC_FAN0_STATUS ; 
 int ec_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int sony_pic_set_fanspeed(unsigned long value)
{
	return ec_write(SONY_PIC_FAN0_STATUS, value);
}