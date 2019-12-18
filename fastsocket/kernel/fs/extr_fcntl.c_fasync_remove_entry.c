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
struct file {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_flags; } ;
struct fasync_struct {struct fasync_struct* fa_next; struct file* fa_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  FASYNC ; 
 int /*<<< orphan*/  fasync_cache ; 
 int /*<<< orphan*/  fasync_lock ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fasync_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fasync_remove_entry(struct file *filp, struct fasync_struct **fapp)
{
	struct fasync_struct *fa, **fp;
	int result = 0;

	spin_lock(&filp->f_lock);
	write_lock_irq(&fasync_lock);
	for (fp = fapp; (fa = *fp) != NULL; fp = &fa->fa_next) {
		if (fa->fa_file != filp)
			continue;
		*fp = fa->fa_next;
		kmem_cache_free(fasync_cache, fa);
		filp->f_flags &= ~FASYNC;
		result = 1;
		break;
	}
	write_unlock_irq(&fasync_lock);
	spin_unlock(&filp->f_lock);
	return result;
}