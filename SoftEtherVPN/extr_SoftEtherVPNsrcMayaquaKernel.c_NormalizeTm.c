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
typedef  scalar_t__ time_64t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_gmtime_r (scalar_t__*,struct tm*) ; 
 scalar_t__ c_mkgmtime (struct tm*) ; 

void NormalizeTm(struct tm *t)
{
	time_64t tmp;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	tmp = c_mkgmtime(t);
	if (tmp == (time_64t)-1)
	{
		return;
	}

	c_gmtime_r(&tmp, t);
}