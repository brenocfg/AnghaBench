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
struct TYPE_3__ {int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  struct CK_DATE CK_DATE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64ToSystem (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (struct CK_DATE*,int) ; 

void UINT64ToCkDate(void *p_ck_date, UINT64 time64)
{
	SYSTEMTIME st;
	char year[32], month[32], day[32];
	struct CK_DATE *ck_date = (CK_DATE *)p_ck_date;
	// Validate arguments
	if (ck_date == NULL)
	{
		return;
	}

	UINT64ToSystem(&st, time64);

	Format(year, sizeof(year), "%04u", st.wYear);
	Format(month, sizeof(month), "%04u", st.wMonth);
	Format(day, sizeof(day), "%04u", st.wDay);

	Zero(ck_date, sizeof(CK_DATE));

	Copy(ck_date->year, year, 4);
	Copy(ck_date->month, month, 2);
	Copy(ck_date->day, day, 2);
}