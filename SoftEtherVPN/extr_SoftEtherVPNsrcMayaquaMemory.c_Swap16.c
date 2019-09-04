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
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

USHORT Swap16(USHORT value)
{
	USHORT r;
	((BYTE *)&r)[0] = ((BYTE *)&value)[1];
	((BYTE *)&r)[1] = ((BYTE *)&value)[0];
	return r;
}