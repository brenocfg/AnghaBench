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
struct task_struct {int dummy; } ;
struct cgroup_pidlist {int* list; int length; int /*<<< orphan*/  mutex; int /*<<< orphan*/  use_count; } ;
struct cgroup_iter {int dummy; } ;
struct cgroup {int dummy; } ;
typedef  int pid_t ;
typedef  enum cgroup_filetype { ____Placeholder_cgroup_filetype } cgroup_filetype ;

/* Variables and functions */
 int CGROUP_FILE_PROCS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cgroup_iter_end (struct cgroup*,struct cgroup_iter*) ; 
 struct task_struct* cgroup_iter_next (struct cgroup*,struct cgroup_iter*) ; 
 int /*<<< orphan*/  cgroup_iter_start (struct cgroup*,struct cgroup_iter*) ; 
 struct cgroup_pidlist* cgroup_pidlist_find (struct cgroup*,int) ; 
 int cgroup_task_count (struct cgroup*) ; 
 int /*<<< orphan*/  cmppid ; 
 int* pidlist_allocate (int) ; 
 int /*<<< orphan*/  pidlist_free (int*) ; 
 int pidlist_uniq (int**,int) ; 
 int /*<<< orphan*/  sort (int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int task_pid_vnr (struct task_struct*) ; 
 int task_tgid_vnr (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pidlist_array_load(struct cgroup *cgrp, enum cgroup_filetype type,
			      struct cgroup_pidlist **lp)
{
	pid_t *array;
	int length;
	int pid, n = 0; /* used for populating the array */
	struct cgroup_iter it;
	struct task_struct *tsk;
	struct cgroup_pidlist *l;

	/*
	 * If cgroup gets more users after we read count, we won't have
	 * enough space - tough.  This race is indistinguishable to the
	 * caller from the case that the additional cgroup users didn't
	 * show up until sometime later on.
	 */
	length = cgroup_task_count(cgrp);
	array = pidlist_allocate(length);
	if (!array)
		return -ENOMEM;
	/* now, populate the array */
	cgroup_iter_start(cgrp, &it);
	while ((tsk = cgroup_iter_next(cgrp, &it))) {
		if (unlikely(n == length))
			break;
		/* get tgid or pid for procs or tasks file respectively */
		if (type == CGROUP_FILE_PROCS)
			pid = task_tgid_vnr(tsk);
		else
			pid = task_pid_vnr(tsk);
		if (pid > 0) /* make sure to only use valid results */
			array[n++] = pid;
	}
	cgroup_iter_end(cgrp, &it);
	length = n;
	/* now sort & (if procs) strip out duplicates */
	sort(array, length, sizeof(pid_t), cmppid, NULL);
	if (type == CGROUP_FILE_PROCS)
		length = pidlist_uniq(&array, length);
	l = cgroup_pidlist_find(cgrp, type);
	if (!l) {
		pidlist_free(array);
		return -ENOMEM;
	}
	/* store array, freeing old if necessary - lock already held */
	pidlist_free(l->list);
	l->list = array;
	l->length = length;
	l->use_count++;
	up_write(&l->mutex);
	*lp = l;
	return 0;
}