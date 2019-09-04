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
struct timeval {int dummy; } ;

/* Variables and functions */
 int __commpage_gettimeofday_internal (struct timeval*,int /*<<< orphan*/ *) ; 

int
__commpage_gettimeofday(struct timeval *tp)
{
	return __commpage_gettimeofday_internal(tp, NULL);
}