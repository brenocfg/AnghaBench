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
typedef  int BYTE ;

/* Variables and functions */

char B64_CodeToChar(BYTE c)
{
	BYTE r;
	r = '=';
	if (c <= 0x19)
	{
		r = c + 'A';
	}
	if (c >= 0x1a && c <= 0x33)
	{
		r = c - 0x1a + 'a';
	}
	if (c >= 0x34 && c <= 0x3d)
	{
		r = c - 0x34 + '0';
	}
	if (c == 0x3e)
	{
		r = '+';
	}
	if (c == 0x3f)
	{
		r = '/';
	}
	return r;
}