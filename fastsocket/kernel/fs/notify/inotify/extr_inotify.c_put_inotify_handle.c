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
struct inotify_handle {int /*<<< orphan*/  idr; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct inotify_handle*) ; 

__attribute__((used)) static inline void put_inotify_handle(struct inotify_handle *ih)
{
	if (atomic_dec_and_test(&ih->count)) {
		idr_destroy(&ih->idr);
		kfree(ih);
	}
}