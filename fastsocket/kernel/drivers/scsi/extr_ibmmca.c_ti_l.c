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
 int MAX_LOG_DEV ; 

__attribute__((used)) static char *ti_l(int val)
{
	const char hex[16] = "0123456789abcdef";
	static char answer[2];

	answer[1] = (char) (0x0);
	if (val <= MAX_LOG_DEV)
		answer[0] = hex[val];
	else
		answer[0] = '-';
	return (char *) &answer;
}