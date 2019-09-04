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

/* Variables and functions */
 scalar_t__ __month_to_secs (int,int) ; 
 long long __year_to_secs (int,int*) ; 
 int days_in_month (int,int) ; 

__attribute__((used)) static long long rule_to_secs(const int *rule, int year)
{
	int is_leap;
	long long t = __year_to_secs(year, &is_leap);
	int x, m, n, d;
	if (rule[0]!='M') {
		x = rule[1];
		if (rule[0]=='J' && (x < 60 || !is_leap)) x--;
		t += 86400 * x;
	} else {
		m = rule[1];
		n = rule[2];
		d = rule[3];
		t += __month_to_secs(m-1, is_leap);
		int wday = (int)((t + 4*86400) % (7*86400)) / 86400;
		int days = d - wday;
		if (days < 0) days += 7;
		if (n == 5 && days+28 >= days_in_month(m, is_leap)) n = 4;
		t += 86400 * (days + 7*(n-1));
	}
	t += rule[4];
	return t;
}