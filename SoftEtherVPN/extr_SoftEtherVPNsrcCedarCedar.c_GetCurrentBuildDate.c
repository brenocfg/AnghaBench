#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_4__ {int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_DATE_D ; 
 int /*<<< orphan*/  BUILD_DATE_HO ; 
 int /*<<< orphan*/  BUILD_DATE_M ; 
 int /*<<< orphan*/  BUILD_DATE_MI ; 
 int /*<<< orphan*/  BUILD_DATE_SE ; 
 int /*<<< orphan*/  BUILD_DATE_Y ; 
 int /*<<< orphan*/  SystemToUINT64 (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT64 GetCurrentBuildDate()
{
	SYSTEMTIME st;

	Zero(&st, sizeof(st));

	st.wYear = BUILD_DATE_Y;
	st.wMonth = BUILD_DATE_M;
	st.wDay = BUILD_DATE_D;
	st.wHour = BUILD_DATE_HO;
	st.wMinute = BUILD_DATE_MI;
	st.wSecond = BUILD_DATE_SE;

	return SystemToUINT64(&st);
}