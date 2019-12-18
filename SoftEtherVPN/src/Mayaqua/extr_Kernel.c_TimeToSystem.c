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
typedef  int /*<<< orphan*/  time_64t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  TimeToTm (struct tm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TmToSystem (int /*<<< orphan*/ *,struct tm*) ; 

void TimeToSystem(SYSTEMTIME *st, time_64t t)
{
	struct tm tmp;
	// Validate arguments
	if (st == NULL)
	{
		return;
	}

	TimeToTm(&tmp, t);
	TmToSystem(st, &tmp);
}