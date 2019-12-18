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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/ * bfad_tsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_E_INIT_SUCCESS ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_worker(void *ptr)
{
	struct bfad_s *bfad;
	unsigned long   flags;

	bfad = (struct bfad_s *)ptr;

	while (!kthread_should_stop()) {

		/* Send event BFAD_E_INIT_SUCCESS */
		bfa_sm_send_event(bfad, BFAD_E_INIT_SUCCESS);

		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_tsk = NULL;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);

		break;
	}

	return 0;
}