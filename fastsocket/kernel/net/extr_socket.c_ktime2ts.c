#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct TYPE_4__ {scalar_t__ tv64; } ;
typedef  TYPE_1__ ktime_t ;

/* Variables and functions */
 struct timespec ktime_to_timespec (TYPE_1__) ; 

__attribute__((used)) static int ktime2ts(ktime_t kt, struct timespec *ts)
{
	if (kt.tv64) {
		*ts = ktime_to_timespec(kt);
		return 1;
	} else {
		return 0;
	}
}