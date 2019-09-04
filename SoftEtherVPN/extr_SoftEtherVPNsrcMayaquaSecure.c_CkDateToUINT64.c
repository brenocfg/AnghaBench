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
typedef  int /*<<< orphan*/  year ;
struct CK_DATE {int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
typedef  int /*<<< orphan*/  month ;
typedef  int /*<<< orphan*/  day ;
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_3__ {void* wDay; void* wMonth; void* wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SystemToUINT64 (TYPE_1__*) ; 
 void* ToInt (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

UINT64 CkDateToUINT64(struct CK_DATE *ck_date)
{
	SYSTEMTIME st;
	char year[32], month[32], day[32];
	// Validate arguments
	if (ck_date == NULL)
	{
		return 0;
	}

	Zero(year, sizeof(year));
	Zero(month, sizeof(month));
	Zero(day, sizeof(day));

	Copy(year, ck_date->year, 4);
	Copy(month, ck_date->month, 2);
	Copy(day, ck_date->day, 2);

	st.wYear = ToInt(year);
	st.wMonth = ToInt(month);
	st.wDay = ToInt(day);

	return SystemToUINT64(&st);
}