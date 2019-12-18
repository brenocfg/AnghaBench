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
struct audit_watch {int parent; struct audit_watch* path; int /*<<< orphan*/  rules; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct audit_watch*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void audit_put_watch(struct audit_watch *watch)
{
	if (atomic_dec_and_test(&watch->count)) {
		WARN_ON(watch->parent);
		WARN_ON(!list_empty(&watch->rules));
		kfree(watch->path);
		kfree(watch);
	}
}