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
 int /*<<< orphan*/  ikbd_write (char*,int) ; 

void ikbd_clock_set(int year, int month, int day, int hour, int minute, int second)
{
	char cmd[7] = { 0x1B, year, month, day, hour, minute, second };

	ikbd_write(cmd, 7);
}