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

__attribute__((used)) static void put_32(unsigned char *s, unsigned c, int e)
{
	e &= 3;
	s[e^0] = c>>24;
	s[e^1] = c>>16;
	s[e^2] = c>>8;
	s[e^3] = c;
}