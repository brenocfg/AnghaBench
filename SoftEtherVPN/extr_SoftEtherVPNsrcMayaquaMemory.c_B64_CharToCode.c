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

char B64_CharToCode(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c - 'A';
	}
	if (c >= 'a' && c <= 'z')
	{
		return c - 'a' + 0x1a;
	}
	if (c >= '0' && c <= '9')
	{
		return c - '0' + 0x34;
	}
	if (c == '+')
	{
		return 0x3e;
	}
	if (c == '/')
	{
		return 0x3f;
	}
	if (c == '=')
	{
		return -1;
	}
	return 0;
}