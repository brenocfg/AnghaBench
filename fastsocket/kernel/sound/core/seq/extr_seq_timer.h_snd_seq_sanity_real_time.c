#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_1__ snd_seq_real_time_t ;

/* Variables and functions */

__attribute__((used)) static inline void snd_seq_sanity_real_time(snd_seq_real_time_t *tm)
{
	while (tm->tv_nsec >= 1000000000) {
		/* roll-over */
		tm->tv_nsec -= 1000000000;
                tm->tv_sec++;
        }
}