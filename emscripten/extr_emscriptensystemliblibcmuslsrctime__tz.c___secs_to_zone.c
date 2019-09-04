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
typedef  long int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __daylight ; 
 long long __timezone ; 
 char** __tzname ; 
 long long __year_to_secs (long long,int /*<<< orphan*/ ) ; 
 scalar_t__ abbrevs ; 
 int /*<<< orphan*/  do_tzset () ; 
 long long dst_off ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  r0 ; 
 int /*<<< orphan*/  r1 ; 
 long long rule_to_secs (int /*<<< orphan*/ ,long long) ; 
 size_t scan_trans (long long,int,size_t*) ; 
 int* types ; 
 scalar_t__ zi ; 
 scalar_t__ zi_read32 (int*) ; 

void __secs_to_zone(long long t, int local, int *isdst, long *offset, long *oppoff, const char **zonename)
{
	LOCK(lock);

	do_tzset();

	if (zi) {
		size_t alt, i = scan_trans(t, local, &alt);
		if (i != -1) {
			*isdst = types[6*i+4];
			*offset = (int32_t)zi_read32(types+6*i);
			*zonename = (const char *)abbrevs + types[6*i+5];
			if (oppoff) *oppoff = (int32_t)zi_read32(types+6*alt);
			UNLOCK(lock);
			return;
		}
	}

	if (!__daylight) goto std;

	/* FIXME: may be broken if DST changes right at year boundary?
	 * Also, this could be more efficient.*/
	long long y = t / 31556952 + 70;
	while (__year_to_secs(y, 0) > t) y--;
	while (__year_to_secs(y+1, 0) < t) y++;

	long long t0 = rule_to_secs(r0, y);
	long long t1 = rule_to_secs(r1, y);

	if (t0 < t1) {
		if (!local) {
			t0 += __timezone;
			t1 += dst_off;
		}
		if (t >= t0 && t < t1) goto dst;
		goto std;
	} else {
		if (!local) {
			t1 += __timezone;
			t0 += dst_off;
		}
		if (t >= t1 && t < t0) goto std;
		goto dst;
	}
std:
	*isdst = 0;
	*offset = -__timezone;
	if (oppoff) *oppoff = -dst_off;
	*zonename = __tzname[0];
	UNLOCK(lock);
	return;
dst:
	*isdst = 1;
	*offset = -dst_off;
	if (oppoff) *oppoff = -__timezone;
	*zonename = __tzname[1];
	UNLOCK(lock);
}