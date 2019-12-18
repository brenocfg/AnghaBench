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
struct mm_struct {int dummy; } ;
struct linux_binprm {struct mm_struct* mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __bprm_mm_init (struct linux_binprm*) ; 
 int /*<<< orphan*/  current ; 
 int init_new_context (int /*<<< orphan*/ ,struct mm_struct*) ; 
 struct mm_struct* mm_alloc () ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 

int bprm_mm_init(struct linux_binprm *bprm)
{
	int err;
	struct mm_struct *mm = NULL;

	bprm->mm = mm = mm_alloc();
	err = -ENOMEM;
	if (!mm)
		goto err;

	err = init_new_context(current, mm);
	if (err)
		goto err;

	err = __bprm_mm_init(bprm);
	if (err)
		goto err;

	return 0;

err:
	if (mm) {
		bprm->mm = NULL;
		mmdrop(mm);
	}

	return err;
}