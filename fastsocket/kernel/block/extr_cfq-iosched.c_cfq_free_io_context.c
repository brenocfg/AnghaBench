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
struct io_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __call_for_each_cic (struct io_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cic_free_func ; 

__attribute__((used)) static void cfq_free_io_context(struct io_context *ioc)
{
	/*
	 * ioc->refcount is zero here, or we are called from elv_unregister(),
	 * so no more cic's are allowed to be linked into this ioc.  So it
	 * should be ok to iterate over the known list, we will see all cic's
	 * since no new ones are added.
	 */
	__call_for_each_cic(ioc, cic_free_func);
}