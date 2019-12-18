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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
struct thread_requested_policy {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  requested_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  static_assert (int,char*) ; 

uintptr_t
threquested_0(thread_t thread)
{
	static_assert(sizeof(struct thread_requested_policy) == sizeof(uint64_t), "size invariant violated");

	uintptr_t* raw = (uintptr_t*)(void*)&thread->requested_policy;

	return raw[0];
}