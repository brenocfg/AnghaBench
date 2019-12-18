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
struct TYPE_3__ {int wYear; scalar_t__ wDay; scalar_t__ wMonth; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */

USHORT SystemToDosDate(SYSTEMTIME *st)
{
	return (USHORT)(
		((UINT)(st->wYear - 1980) << 9) |
		((UINT)st->wMonth<< 5) |
		(UINT)st->wDay);
}