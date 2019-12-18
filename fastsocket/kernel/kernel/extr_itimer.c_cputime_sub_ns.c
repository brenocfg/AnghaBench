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
typedef  scalar_t__ u32 ;
struct timespec {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  cputime_t ;

/* Variables and functions */
 int /*<<< orphan*/  cputime_to_timespec (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ timespec_to_ns (struct timespec*) ; 

__attribute__((used)) static inline u32 cputime_sub_ns(cputime_t ct, s64 real_ns)
{
	struct timespec ts;
	s64 cpu_ns;

	cputime_to_timespec(ct, &ts);
	cpu_ns = timespec_to_ns(&ts);

	return (cpu_ns <= real_ns) ? 0 : cpu_ns - real_ns;
}