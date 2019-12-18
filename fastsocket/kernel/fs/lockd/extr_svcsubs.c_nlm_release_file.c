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
struct nlm_file {scalar_t__ f_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct nlm_file*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_delete_file (struct nlm_file*) ; 
 int /*<<< orphan*/  nlm_file_inuse (struct nlm_file*) ; 
 int /*<<< orphan*/  nlm_file_mutex ; 

void
nlm_release_file(struct nlm_file *file)
{
	dprintk("lockd: nlm_release_file(%p, ct = %d)\n",
				file, file->f_count);

	/* Lock file table */
	mutex_lock(&nlm_file_mutex);

	/* If there are no more locks etc, delete the file */
	if (--file->f_count == 0 && !nlm_file_inuse(file))
		nlm_delete_file(file);

	mutex_unlock(&nlm_file_mutex);
}