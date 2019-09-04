#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  int UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Unknown; int /*<<< orphan*/  SpanSecond; int /*<<< orphan*/  SpanMinute; int /*<<< orphan*/  SpanHour; int /*<<< orphan*/  SpanDay; int /*<<< orphan*/ * DayOfWeek; int /*<<< orphan*/  SecondStr; int /*<<< orphan*/  MinuteStr; int /*<<< orphan*/  HourStr; int /*<<< orphan*/  DayStr; int /*<<< orphan*/  MonthStr; int /*<<< orphan*/  YearStr; } ;
typedef  TYPE_2__ LOCALE ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_LOCALE_STR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 TYPE_1__* UniParseToken (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool LoadLocale(LOCALE *locale, wchar_t *str)
{
	UNI_TOKEN_LIST *tokens;
	UINT i;
	// Validate arguments
	if (locale == NULL || str == NULL)
	{
		return false;
	}

	// Analysis of the token
	tokens = UniParseToken(str, L" ");
	if (tokens->NumTokens != 18)
	{
		UniFreeToken(tokens);
		return false;
	}

	// Set to the structure
	Zero(locale, sizeof(LOCALE));
	COPY_LOCALE_STR(locale->YearStr, sizeof(locale->YearStr), tokens->Token[0]);
	COPY_LOCALE_STR(locale->MonthStr, sizeof(locale->MonthStr), tokens->Token[1]);
	COPY_LOCALE_STR(locale->DayStr, sizeof(locale->DayStr), tokens->Token[2]);
	COPY_LOCALE_STR(locale->HourStr, sizeof(locale->HourStr), tokens->Token[3]);
	COPY_LOCALE_STR(locale->MinuteStr, sizeof(locale->MinuteStr), tokens->Token[4]);
	COPY_LOCALE_STR(locale->SecondStr, sizeof(locale->SecondStr), tokens->Token[5]);

	for (i = 0;i < 7;i++)
	{
		COPY_LOCALE_STR(locale->DayOfWeek[i], sizeof(locale->DayOfWeek[i]),
			tokens->Token[6 + i]);
	}

	COPY_LOCALE_STR(locale->SpanDay, sizeof(locale->SpanDay), tokens->Token[13]);
	COPY_LOCALE_STR(locale->SpanHour, sizeof(locale->SpanHour), tokens->Token[14]);
	COPY_LOCALE_STR(locale->SpanMinute, sizeof(locale->SpanMinute), tokens->Token[15]);
	COPY_LOCALE_STR(locale->SpanSecond, sizeof(locale->SpanSecond), tokens->Token[16]);

	COPY_LOCALE_STR(locale->Unknown, sizeof(locale->Unknown), tokens->Token[17]);

	UniFreeToken(tokens);
	return true;
}