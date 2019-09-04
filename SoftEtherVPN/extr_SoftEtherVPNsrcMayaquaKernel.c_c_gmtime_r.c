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

/* Variables and functions */
 int /*<<< orphan*/  c_timesub (int /*<<< orphan*/  const*,long,struct tm*) ; 

struct tm * c_gmtime_r(const time_64t* timep, struct tm *tm)
{
	c_timesub(timep, 0L, tm);
	return tm;
}