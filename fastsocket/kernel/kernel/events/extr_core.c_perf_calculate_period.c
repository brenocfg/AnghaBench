#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int sample_freq; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  REDUCE_FLS (int,int) ; 
 int div64_u64 (int,int) ; 
 int fls64 (int) ; 

__attribute__((used)) static u64 perf_calculate_period(struct perf_event *event, u64 nsec, u64 count)
{
	u64 frequency = event->attr.sample_freq;
	u64 sec = NSEC_PER_SEC;
	u64 divisor, dividend;

	int count_fls, nsec_fls, frequency_fls, sec_fls;

	count_fls = fls64(count);
	nsec_fls = fls64(nsec);
	frequency_fls = fls64(frequency);
	sec_fls = 30;

	/*
	 * We got @count in @nsec, with a target of sample_freq HZ
	 * the target period becomes:
	 *
	 *             @count * 10^9
	 * period = -------------------
	 *          @nsec * sample_freq
	 *
	 */

	/*
	 * Reduce accuracy by one bit such that @a and @b converge
	 * to a similar magnitude.
	 */
#define REDUCE_FLS(a, b)		\
do {					\
	if (a##_fls > b##_fls) {	\
		a >>= 1;		\
		a##_fls--;		\
	} else {			\
		b >>= 1;		\
		b##_fls--;		\
	}				\
} while (0)

	/*
	 * Reduce accuracy until either term fits in a u64, then proceed with
	 * the other, so that finally we can do a u64/u64 division.
	 */
	while (count_fls + sec_fls > 64 && nsec_fls + frequency_fls > 64) {
		REDUCE_FLS(nsec, frequency);
		REDUCE_FLS(sec, count);
	}

	if (count_fls + sec_fls > 64) {
		divisor = nsec * frequency;

		while (count_fls + sec_fls > 64) {
			REDUCE_FLS(count, sec);
			divisor >>= 1;
		}

		dividend = count * sec;
	} else {
		dividend = count * sec;

		while (nsec_fls + frequency_fls > 64) {
			REDUCE_FLS(nsec, frequency);
			dividend >>= 1;
		}

		divisor = nsec * frequency;
	}

	if (!divisor)
		return dividend;

	return div64_u64(dividend, divisor);
}