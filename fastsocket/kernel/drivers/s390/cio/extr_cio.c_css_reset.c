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
struct chp_id {int id; } ;

/* Variables and functions */
 int RCHP_TIMEOUT ; 
 int __MAX_CHPID ; 
 int /*<<< orphan*/  __ctl_clear_bit (int,int) ; 
 int /*<<< orphan*/  __ctl_set_bit (int,int) ; 
 int /*<<< orphan*/  __shutdown_subchannel_easy ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chp_id_init (struct chp_id*) ; 
 int /*<<< orphan*/  chpid_reset_count ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  for_each_subchannel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long long get_clock () ; 
 int /*<<< orphan*/  local_mcck_disable () ; 
 int /*<<< orphan*/  local_mcck_enable () ; 
 int rchp (struct chp_id) ; 
 int /*<<< orphan*/ * s390_base_mcck_handler_fn ; 
 int /*<<< orphan*/ * s390_reset_chpids_mcck_handler ; 

__attribute__((used)) static void css_reset(void)
{
	int i, ret;
	unsigned long long timeout;
	struct chp_id chpid;

	/* Reset subchannels. */
	for_each_subchannel(__shutdown_subchannel_easy,  NULL);
	/* Reset channel paths. */
	s390_base_mcck_handler_fn = s390_reset_chpids_mcck_handler;
	/* Enable channel report machine checks. */
	__ctl_set_bit(14, 28);
	/* Temporarily reenable machine checks. */
	local_mcck_enable();
	chp_id_init(&chpid);
	for (i = 0; i <= __MAX_CHPID; i++) {
		chpid.id = i;
		ret = rchp(chpid);
		if ((ret == 0) || (ret == 2))
			/*
			 * rchp either succeeded, or another rchp is already
			 * in progress. In either case, we'll get a crw.
			 */
			atomic_inc(&chpid_reset_count);
	}
	/* Wait for machine check for all channel paths. */
	timeout = get_clock() + (RCHP_TIMEOUT << 12);
	while (atomic_read(&chpid_reset_count) != 0) {
		if (get_clock() > timeout)
			break;
		cpu_relax();
	}
	/* Disable machine checks again. */
	local_mcck_disable();
	/* Disable channel report machine checks. */
	__ctl_clear_bit(14, 28);
	s390_base_mcck_handler_fn = NULL;
}