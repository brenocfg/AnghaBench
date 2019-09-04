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
typedef  int /*<<< orphan*/  sched_mode_t ;
typedef  int integer_t ;

/* Variables and functions */
#define  POLICY_FIFO 130 
#define  POLICY_RR 129 
#define  POLICY_TIMESHARE 128 
 int /*<<< orphan*/  TH_MODE_FIXED ; 
 int /*<<< orphan*/  TH_MODE_NONE ; 
 int /*<<< orphan*/  TH_MODE_TIMESHARE ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static sched_mode_t
convert_policy_to_sched_mode(integer_t policy) {
	switch (policy) {
		case POLICY_TIMESHARE:
			return TH_MODE_TIMESHARE;
		case POLICY_RR:
		case POLICY_FIFO:
			return TH_MODE_FIXED;
		default:
			panic("unexpected sched policy: %d", policy);
			return TH_MODE_NONE;
	}
}