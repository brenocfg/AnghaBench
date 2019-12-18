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
struct fasync_struct {int fa_fd; struct fasync_struct* fa_next; struct file* fa_file; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FASYNC ; 
 int /*<<< orphan*/  FASYNC_MAGIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fasync_cache ; 
 int /*<<< orphan*/  fasync_lock ; 
 struct fasync_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fasync_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fasync_add_entry(int fd, struct file *filp, struct fasync_struct **fapp)
{
	struct fasync_struct *new, *fa, **fp;
	int result = 0;

	new = kmem_cache_alloc(fasync_cache, GFP_KERNEL);
	if (!new)
		return -ENOMEM;

	spin_lock(&filp->f_lock);
	write_lock_irq(&fasync_lock);
	for (fp = fapp; (fa = *fp) != NULL; fp = &fa->fa_next) {
		if (fa->fa_file != filp)
			continue;
		fa->fa_fd = fd;
		kmem_cache_free(fasync_cache, new);
		goto out;
	}

	new->magic = FASYNC_MAGIC;
	new->fa_file = filp;
	new->fa_fd = fd;
	new->fa_next = *fapp;
	*fapp = new;
	result = 1;
	filp->f_flags |= FASYNC;

out:
	write_unlock_irq(&fasync_lock);
	spin_unlock(&filp->f_lock);
	return result;
}