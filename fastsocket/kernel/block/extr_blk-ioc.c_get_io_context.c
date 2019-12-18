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
struct io_context {int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct io_context* current_io_context (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

struct io_context *get_io_context(gfp_t gfp_flags, int node)
{
	struct io_context *ret = NULL;

	/*
	 * Check for unlikely race with exiting task. ioc ref count is
	 * zero when ioc is being detached.
	 */
	do {
		ret = current_io_context(gfp_flags, node);
		if (unlikely(!ret))
			break;
	} while (!atomic_long_inc_not_zero(&ret->refcount));

	return ret;
}