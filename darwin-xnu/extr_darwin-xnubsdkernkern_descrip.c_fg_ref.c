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
struct fileproc {struct fileglob* f_fglob; } ;
struct fileglob {int /*<<< orphan*/  fg_lock; int /*<<< orphan*/  fg_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
fg_ref(struct fileproc * fp)
{
	struct fileglob *fg;

	fg = fp->f_fglob;

	lck_mtx_lock_spin(&fg->fg_lock);

#if DIAGNOSTIC
	if ((fp->f_flags & ~((unsigned int)FP_VALID_FLAGS)) != 0)
		panic("fg_ref: invalid bits on fp %p", fp);

	if (fg->fg_count == 0)
		panic("fg_ref: adding fgcount to zeroed fg: fp %p fg %p",
		    fp, fg);
#endif
	fg->fg_count++;
	lck_mtx_unlock(&fg->fg_lock);
}