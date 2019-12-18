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
typedef  scalar_t__ UINT64 ;
struct TYPE_4__ {int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG_BETA_EXPIRES_DAY ; 
 int /*<<< orphan*/  ELOG_BETA_EXPIRES_MONTH ; 
 int /*<<< orphan*/  ELOG_BETA_EXPIRES_YEAR ; 
 int ELOG_IS_BETA ; 
 scalar_t__ LocalTime64 () ; 
 scalar_t__ SystemToUINT64 (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool ElIsBetaExpired()
{
	SYSTEMTIME st;
	UINT64 expires64;
	UINT64 now64;
	if (ELOG_IS_BETA == false)
	{
		return false;
	}

	Zero(&st, sizeof(st));

	st.wYear = ELOG_BETA_EXPIRES_YEAR;
	st.wMonth = ELOG_BETA_EXPIRES_MONTH;
	st.wDay = ELOG_BETA_EXPIRES_DAY;

	expires64 = SystemToUINT64(&st);
	now64 = LocalTime64();

	if (now64 >= expires64)
	{
		return true;
	}

	return false;
}