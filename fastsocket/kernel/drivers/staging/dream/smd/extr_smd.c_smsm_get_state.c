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
typedef  int uint32_t ;
struct smsm_shared {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID_SHARED_STATE ; 
 int SMSM_RESET ; 
 int /*<<< orphan*/  handle_modem_crash () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct smsm_shared* smem_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smem_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

uint32_t smsm_get_state(void)
{
	unsigned long flags;
	struct smsm_shared *smsm;
	uint32_t rv;

	spin_lock_irqsave(&smem_lock, flags);

	smsm = smem_alloc(ID_SHARED_STATE,
			  2 * sizeof(struct smsm_shared));

	if (smsm)
		rv = smsm[1].state;
	else
		rv = 0;

	if (rv & SMSM_RESET)
		handle_modem_crash();

	spin_unlock_irqrestore(&smem_lock, flags);

	if (smsm == NULL)
		pr_err("smsm_get_state <SM NO STATE>\n");
	return rv;
}