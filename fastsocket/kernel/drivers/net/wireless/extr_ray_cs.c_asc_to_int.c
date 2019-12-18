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

__attribute__((used)) static int asc_to_int(char a)
{
	if (a < '0')
		return -1;
	if (a <= '9')
		return (a - '0');
	if (a < 'A')
		return -1;
	if (a <= 'F')
		return (10 + a - 'A');
	if (a < 'a')
		return -1;
	if (a <= 'f')
		return (10 + a - 'a');
	return -1;
}