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
struct multipath {scalar_t__ queue_if_no_path; scalar_t__ saved_queue_if_no_path; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 scalar_t__ dm_noflush_suspending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __must_push_back(struct multipath *m)
{
	return (m->queue_if_no_path != m->saved_queue_if_no_path &&
		dm_noflush_suspending(m->ti));
}