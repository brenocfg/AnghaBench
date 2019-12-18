#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  fu_list; } ;
struct file {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_cred; TYPE_2__ f_owner; int /*<<< orphan*/  f_count; TYPE_1__ f_u; } ;
struct cred {int dummy; } ;
struct TYPE_6__ {long max_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  eventpoll_init_file (struct file*) ; 
 int /*<<< orphan*/  file_free (struct file*) ; 
 TYPE_3__ files_stat ; 
 int /*<<< orphan*/  filp_cachep ; 
 int /*<<< orphan*/  get_cred (struct cred const*) ; 
 int /*<<< orphan*/  get_max_files () ; 
 long get_nr_files () ; 
 struct file* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_files ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_counter_sum_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ security_file_alloc (struct file*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct file *get_empty_filp(void)
{
	const struct cred *cred = current_cred();
	static long old_max;
	struct file * f;

	/*
	 * Privileged users can go above max_files
	 */
	if (get_nr_files() >= files_stat.max_files && !capable(CAP_SYS_ADMIN)) {
		/*
		 * percpu_counters are inaccurate.  Do an expensive check before
		 * we go and fail.
		 */
		if (percpu_counter_sum_positive(&nr_files) >= files_stat.max_files)
			goto over;
	}

	f = kmem_cache_zalloc(filp_cachep, GFP_KERNEL);
	if (f == NULL)
		goto fail;

	percpu_counter_inc(&nr_files);
	if (security_file_alloc(f))
		goto fail_sec;

	INIT_LIST_HEAD(&f->f_u.fu_list);
	atomic_long_set(&f->f_count, 1);
	rwlock_init(&f->f_owner.lock);
	f->f_cred = get_cred(cred);
	spin_lock_init(&f->f_lock);
	eventpoll_init_file(f);
	/* f->f_version: 0 */
	return f;

over:
	/* Ran out of filps - report that */
	if (get_nr_files() > old_max) {
		pr_info("VFS: file-max limit %lu reached\n", get_max_files());
		old_max = get_nr_files();
	}
	goto fail;

fail_sec:
	file_free(f);
fail:
	return NULL;
}