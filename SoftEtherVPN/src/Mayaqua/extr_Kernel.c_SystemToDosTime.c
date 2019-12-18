#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
struct TYPE_3__ {scalar_t__ wSecond; scalar_t__ wMinute; scalar_t__ wHour; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */

USHORT SystemToDosTime(SYSTEMTIME *st)
{
	return (USHORT)(
		((UINT)st->wHour << 11) |
		((UINT)st->wMinute << 5) |
		((UINT)st->wSecond >> 1));
}