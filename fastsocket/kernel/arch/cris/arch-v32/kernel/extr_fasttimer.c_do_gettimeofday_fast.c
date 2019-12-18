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
struct fasttime_t {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_jiff; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_JIFFIES_USEC () ; 
 int /*<<< orphan*/  jiffies ; 

inline void do_gettimeofday_fast(struct fasttime_t *tv)
{
	tv->tv_jiff = jiffies;
	tv->tv_usec = GET_JIFFIES_USEC();
}