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
struct sbridge_pvt {unsigned int mce_out; unsigned int mce_in; struct mce* mce_outentry; scalar_t__ mce_overrun; int /*<<< orphan*/ * mce_entry; } ;
struct mem_ctl_info {struct sbridge_pvt* pvt_info; } ;
struct mce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 unsigned int MCE_LOG_LEN ; 
 int /*<<< orphan*/  memcpy (struct mce*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sbridge_mce_output_error (struct mem_ctl_info*,struct mce*) ; 
 int /*<<< orphan*/  sbridge_printk (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void sbridge_check_error(struct mem_ctl_info *mci)
{
	struct sbridge_pvt *pvt = mci->pvt_info;
	int i;
	unsigned count = 0;
	struct mce *m;

	/*
	 * MCE first step: Copy all mce errors into a temporary buffer
	 * We use a double buffering here, to reduce the risk of
	 * loosing an error.
	 */
	smp_rmb();
	count = (pvt->mce_out + MCE_LOG_LEN - pvt->mce_in)
		% MCE_LOG_LEN;
	if (!count)
		return;

	m = pvt->mce_outentry;
	if (pvt->mce_in + count > MCE_LOG_LEN) {
		unsigned l = MCE_LOG_LEN - pvt->mce_in;

		memcpy(m, &pvt->mce_entry[pvt->mce_in], sizeof(*m) * l);
		smp_wmb();
		pvt->mce_in = 0;
		count -= l;
		m += l;
	}
	memcpy(m, &pvt->mce_entry[pvt->mce_in], sizeof(*m) * count);
	smp_wmb();
	pvt->mce_in += count;

	smp_rmb();
	if (pvt->mce_overrun) {
		sbridge_printk(KERN_ERR, "Lost %d memory errors\n",
			      pvt->mce_overrun);
		smp_wmb();
		pvt->mce_overrun = 0;
	}

	/*
	 * MCE second step: parse errors and display
	 */
	for (i = 0; i < count; i++)
		sbridge_mce_output_error(mci, &pvt->mce_outentry[i]);
}