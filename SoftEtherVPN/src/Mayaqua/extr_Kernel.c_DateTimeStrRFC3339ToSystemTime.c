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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  str_year ;
typedef  int /*<<< orphan*/  str_second ;
typedef  int /*<<< orphan*/  str_msec ;
typedef  int /*<<< orphan*/  str_month ;
typedef  int /*<<< orphan*/  str_minute ;
typedef  int /*<<< orphan*/  str_hour ;
typedef  int /*<<< orphan*/  str_day ;
typedef  size_t UINT ;
struct TYPE_5__ {void* wMilliseconds; void* wSecond; void* wMinute; void* wHour; void* wDay; void* wMonth; void* wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 size_t INFINITE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NormalizeSystem (TYPE_1__*) ; 
 size_t SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 void* ToInt (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool DateTimeStrRFC3339ToSystemTime(SYSTEMTIME *st, char *str)
{
	bool ok = false;
	UINT index_plus;
	char tmp[MAX_PATH];
	Zero(st, sizeof(SYSTEMTIME));
	if (st == NULL || str == NULL)
	{
		return false;
	}

	StrCpy(tmp, sizeof(tmp), str);

	index_plus = SearchStrEx(tmp, "+", 0, false);
	if (index_plus != INFINITE)
	{
		tmp[index_plus] = 0;
	}

	if (StrLen(tmp) >= 19)
	{
		if (tmp[4] == '-' && tmp[7] == '-' && tmp[10] == 'T' && tmp[13] == ':' &&
			tmp[16] == ':')
		{
			char str_year[16], str_month[16], str_day[16], str_hour[16], str_minute[16],
				str_second[16], str_msec[16];

			StrCpy(str_year, sizeof(str_year), tmp + 0);
			str_year[4] = 0;

			StrCpy(str_month, sizeof(str_month), tmp + 5);
			str_month[2] = 0;

			StrCpy(str_day, sizeof(str_day), tmp + 8);
			str_day[2] = 0;

			StrCpy(str_hour, sizeof(str_hour), tmp + 11);
			str_hour[2] = 0;

			StrCpy(str_minute, sizeof(str_minute), tmp + 14);
			str_minute[2] = 0;

			StrCpy(str_second, sizeof(str_second), tmp + 17);
			str_second[2] = 0;

			str_msec[0] = 0;

			if (StrLen(tmp) >= 21 && tmp[19] == '.')
			{
				StrCpy(str_msec, sizeof(str_msec), tmp + 20);
				str_msec[StrLen(tmp) - 21] = 0;
				while (StrLen(str_msec) < 3)
				{
					StrCat(str_msec, sizeof(str_msec), "0");
				}
				str_msec[3] = 0;
			}

			st->wYear = ToInt(str_year);
			st->wMonth = ToInt(str_month);
			st->wDay = ToInt(str_day);
			st->wHour = ToInt(str_hour);
			st->wMinute = ToInt(str_minute);
			st->wSecond = ToInt(str_second);
			st->wMilliseconds = ToInt(str_msec);

			NormalizeSystem(st);

			ok = true;
		}
	}

	return ok;
}