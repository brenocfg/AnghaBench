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
struct audpp_state {int /*<<< orphan*/  lock; scalar_t__ enabled; int /*<<< orphan*/  mod; int /*<<< orphan*/ ** private; int /*<<< orphan*/ ** func; scalar_t__ open_count; } ;
typedef  int /*<<< orphan*/ * audpp_event_func ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_MSG_CFG_MSG ; 
 int /*<<< orphan*/  AUDPP_MSG_ENA_ENA ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  EV_ENABLE ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adsp_ops ; 
 int /*<<< orphan*/  audpp_dsp_config (int) ; 
 int /*<<< orphan*/  audpp_fake_event (struct audpp_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  msm_adsp_enable (int /*<<< orphan*/ ) ; 
 int msm_adsp_get (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct audpp_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct audpp_state the_audpp_state ; 

int audpp_enable(int id, audpp_event_func func, void *private)
{
	struct audpp_state *audpp = &the_audpp_state;
	int res = 0;

	if (id < -1 || id > 4)
		return -EINVAL;

	if (id == -1)
		id = 5;

	mutex_lock(audpp->lock);
	if (audpp->func[id]) {
		res = -EBUSY;
		goto out;
	}

	audpp->func[id] = func;
	audpp->private[id] = private;

	LOG(EV_ENABLE, 1);
	if (audpp->open_count++ == 0) {
		pr_info("audpp: enable\n");
		res = msm_adsp_get("AUDPPTASK", &audpp->mod, &adsp_ops, audpp);
		if (res < 0) {
			pr_err("audpp: cannot open AUDPPTASK\n");
			audpp->open_count = 0;
			audpp->func[id] = NULL;
			audpp->private[id] = NULL;
			goto out;
		}
		LOG(EV_ENABLE, 2);
		msm_adsp_enable(audpp->mod);
		audpp_dsp_config(1);
	} else {
		unsigned long flags;
		local_irq_save(flags);
		if (audpp->enabled)
			audpp_fake_event(audpp, id,
					 AUDPP_MSG_CFG_MSG, AUDPP_MSG_ENA_ENA);
		local_irq_restore(flags);
	}

	res = 0;
out:
	mutex_unlock(audpp->lock);
	return res;
}