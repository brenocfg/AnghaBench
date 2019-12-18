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
typedef  int /*<<< orphan*/  u64 ;
struct timecounter {int /*<<< orphan*/  nsec; int /*<<< orphan*/  cycle_last; struct cyclecounter const* cc; } ;
struct cyclecounter {int /*<<< orphan*/  (* read ) (struct cyclecounter const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cyclecounter const*) ; 

void timecounter_init(struct timecounter *tc,
		      const struct cyclecounter *cc,
		      u64 start_tstamp)
{
	tc->cc = cc;
	tc->cycle_last = cc->read(cc);
	tc->nsec = start_tstamp;
}