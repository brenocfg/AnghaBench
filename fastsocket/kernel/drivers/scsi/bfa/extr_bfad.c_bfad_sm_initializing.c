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
typedef  enum bfad_sm_event { ____Placeholder_bfad_sm_event } bfad_sm_event ;

/* Variables and functions */
#define  BFAD_E_INIT_FAILED 130 
#define  BFAD_E_INIT_SUCCESS 129 
#define  BFAD_E_INTR_INIT_FAILED 128 
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_sm_fault (struct bfad_s*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int) ; 
 int /*<<< orphan*/  bfad_sm_failed ; 
 int /*<<< orphan*/  bfad_sm_operational ; 
 int /*<<< orphan*/  bfad_sm_uninit ; 
 int bfad_start_ops (struct bfad_s*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bfad_sm_initializing(struct bfad_s *bfad, enum bfad_sm_event event)
{
	int	retval;
	unsigned long	flags;

	bfa_trc(bfad, event);

	switch (event) {
	case BFAD_E_INIT_SUCCESS:
		kthread_stop(bfad->bfad_tsk);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_tsk = NULL;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);

		retval = bfad_start_ops(bfad);
		if (retval != BFA_STATUS_OK)
			break;
		bfa_sm_set_state(bfad, bfad_sm_operational);
		break;

	case BFAD_E_INTR_INIT_FAILED:
		bfa_sm_set_state(bfad, bfad_sm_uninit);
		kthread_stop(bfad->bfad_tsk);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_tsk = NULL;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		break;

	case BFAD_E_INIT_FAILED:
		bfa_sm_set_state(bfad, bfad_sm_failed);
		break;
	default:
		bfa_sm_fault(bfad, event);
	}
}