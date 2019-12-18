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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetDateTimeStr64 (char*,int,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void GetDateTimeStr64Uni(wchar_t *str, UINT size, UINT64 sec64)
{
	char tmp[MAX_SIZE];
	if (str == NULL)
	{
		return;
	}

	GetDateTimeStr64(tmp, sizeof(tmp), sec64);
	StrToUni(str, size, tmp);
}