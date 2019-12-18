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
struct dm_exception_store {int dummy; } ;
struct dm_exception {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void transient_commit_exception(struct dm_exception_store *store,
				       struct dm_exception *e,
				       void (*callback) (void *, int success),
				       void *callback_context)
{
	/* Just succeed */
	callback(callback_context, 1);
}