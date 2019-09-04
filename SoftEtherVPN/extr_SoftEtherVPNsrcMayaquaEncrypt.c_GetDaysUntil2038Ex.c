#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  now ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int wYear; int wMonth; int wDay; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetDaysUntil2038 () ; 
 int /*<<< orphan*/  SystemTime (TYPE_1__*) ; 
 scalar_t__ SystemTime64 () ; 
 scalar_t__ SystemToUINT64 (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT GetDaysUntil2038Ex()
{
	SYSTEMTIME now;

	Zero(&now, sizeof(now));
	SystemTime(&now);

	if (now.wYear >= 2030)
	{
		UINT64 now = SystemTime64();
		UINT64 target;
		SYSTEMTIME st;

		Zero(&st, sizeof(st));
		st.wYear = 2049;
		st.wMonth = 12;
		st.wDay = 30;

		target = SystemToUINT64(&st);

		if (now >= target)
		{
			return 0;
		}
		else
		{
			return (UINT)((target - now) / (UINT64)(1000 * 60 * 60 * 24));
		}
	}
	else
	{
		return GetDaysUntil2038();
	}
}