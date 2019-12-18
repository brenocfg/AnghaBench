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
struct uthread {int /*<<< orphan*/  uu_workq_stackaddr; } ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */

__attribute__((used)) static inline event_t
workq_parked_wait_event(struct uthread *uth)
{
	return (event_t)&uth->uu_workq_stackaddr;
}