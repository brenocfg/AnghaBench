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
typedef  int UCHAR ;

/* Variables and functions */

bool IsPrintableAsciiChar(char c)
{
	UCHAR uc = (UCHAR)c;
	if (uc <= 31)
	{
		return false;
	}
	if (uc >= 127)
	{
		return false;
	}
	return true;
}