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
struct dtl {int /*<<< orphan*/  lock; scalar_t__ buf_entries; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dtl_stop (struct dtl*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dtl_disable(struct dtl *dtl)
{
	spin_lock(&dtl->lock);
	dtl_stop(dtl);

	kfree(dtl->buf);
	dtl->buf = NULL;
	dtl->buf_entries = 0;
	spin_unlock(&dtl->lock);
}