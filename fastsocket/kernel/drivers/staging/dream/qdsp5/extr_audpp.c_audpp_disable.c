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
struct audpp_state {void** private; scalar_t__ open_count; int /*<<< orphan*/  lock; int /*<<< orphan*/ * mod; int /*<<< orphan*/ ** func; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_MSG_CFG_MSG ; 
 int /*<<< orphan*/  AUDPP_MSG_ENA_DIS ; 
 int /*<<< orphan*/  EV_DISABLE ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  audpp_dsp_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audpp_fake_event (struct audpp_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  msm_adsp_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_adsp_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct audpp_state the_audpp_state ; 

void audpp_disable(int id, void *private)
{
	struct audpp_state *audpp = &the_audpp_state;
	unsigned long flags;

	if (id < -1 || id > 4)
		return;

	if (id == -1)
		id = 5;

	mutex_lock(audpp->lock);
	LOG(EV_DISABLE, 1);
	if (!audpp->func[id])
		goto out;
	if (audpp->private[id] != private)
		goto out;

	local_irq_save(flags);
	audpp_fake_event(audpp, id, AUDPP_MSG_CFG_MSG, AUDPP_MSG_ENA_DIS);
	audpp->func[id] = NULL;
	audpp->private[id] = NULL;
	local_irq_restore(flags);

	if (--audpp->open_count == 0) {
		pr_info("audpp: disable\n");
		LOG(EV_DISABLE, 2);
		audpp_dsp_config(0);
		msm_adsp_disable(audpp->mod);
		msm_adsp_put(audpp->mod);
		audpp->mod = NULL;
	}
out:
	mutex_unlock(audpp->lock);
}