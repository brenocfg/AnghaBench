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
typedef  double uint64_t ;
struct TYPE_2__ {scalar_t__ numer; scalar_t__ denom; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ sched_mti ; 
 int /*<<< orphan*/  sched_mti_init ; 
 int /*<<< orphan*/  sched_mti_once_control ; 

uint64_t
nanoseconds_to_absolutetime(uint64_t nanoseconds)
{
	pthread_once(&sched_mti_once_control, sched_mti_init);

	return (uint64_t)(nanoseconds * (((double)sched_mti.denom) / ((double)sched_mti.numer)));
}