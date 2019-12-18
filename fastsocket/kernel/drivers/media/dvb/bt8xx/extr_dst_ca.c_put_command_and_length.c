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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static void put_command_and_length(u8 *data, int command, int length)
{
	data[0] = (command >> 16) & 0xff;
	data[1] = (command >> 8) & 0xff;
	data[2] = command & 0xff;
	data[3] = length;
}