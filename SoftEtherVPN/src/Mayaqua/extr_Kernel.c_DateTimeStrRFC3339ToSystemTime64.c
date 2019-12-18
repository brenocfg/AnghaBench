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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 scalar_t__ DateTimeStrRFC3339ToSystemTime (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SystemToUINT64 (int /*<<< orphan*/ *) ; 

UINT64 DateTimeStrRFC3339ToSystemTime64(char *str)
{
	SYSTEMTIME st;
	if (DateTimeStrRFC3339ToSystemTime(&st, str))
	{
		return SystemToUINT64(&st);
	}
	else
	{
		return 0;
	}
}