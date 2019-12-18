#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int config; } ;
struct TYPE_3__ {scalar_t__ type; int config; int /*<<< orphan*/  exclude_user; int /*<<< orphan*/  exclude_kernel; } ;
struct perf_event {TYPE_2__ hw; TYPE_1__ attr; } ;
struct p4_event_bind {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  P4_CCCR_ESEL (unsigned int) ; 
 int P4_CONFIG_MASK ; 
 unsigned int P4_OPCODE_ESEL (int /*<<< orphan*/ ) ; 
 scalar_t__ PERF_TYPE_RAW ; 
 int get_cpu () ; 
 struct p4_event_bind* p4_config_get_bind (int) ; 
 int p4_config_pack_cccr (int /*<<< orphan*/ ) ; 
 int p4_config_pack_escr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4_default_cccr_conf (int) ; 
 int /*<<< orphan*/  p4_default_escr_conf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ p4_ht_active () ; 
 scalar_t__ p4_ht_thread (int) ; 
 int p4_set_ht_bit (int) ; 
 int p4_validate_raw_event (struct perf_event*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int x86_setup_perfctr (struct perf_event*) ; 

__attribute__((used)) static int p4_hw_config(struct perf_event *event)
{
	int cpu = get_cpu();
	int rc = 0;
	u32 escr, cccr;

	/*
	 * the reason we use cpu that early is that: if we get scheduled
	 * first time on the same cpu -- we will not need swap thread
	 * specific flags in config (and will save some cpu cycles)
	 */

	cccr = p4_default_cccr_conf(cpu);
	escr = p4_default_escr_conf(cpu, event->attr.exclude_kernel,
					 event->attr.exclude_user);
	event->hw.config = p4_config_pack_escr(escr) |
			   p4_config_pack_cccr(cccr);

	if (p4_ht_active() && p4_ht_thread(cpu))
		event->hw.config = p4_set_ht_bit(event->hw.config);

	if (event->attr.type == PERF_TYPE_RAW) {
		struct p4_event_bind *bind;
		unsigned int esel;
		/*
		 * Clear bits we reserve to be managed by kernel itself
		 * and never allowed from a user space
		 */
		 event->attr.config &= P4_CONFIG_MASK;

		rc = p4_validate_raw_event(event);
		if (rc)
			goto out;

		/*
		 * Note that for RAW events we allow user to use P4_CCCR_RESERVED
		 * bits since we keep additional info here (for cache events and etc)
		 */
		event->hw.config |= event->attr.config;
		bind = p4_config_get_bind(event->attr.config);
		if (!bind) {
			rc = -EINVAL;
			goto out;
		}
		esel = P4_OPCODE_ESEL(bind->opcode);
		event->hw.config |= p4_config_pack_cccr(P4_CCCR_ESEL(esel));
	}

	rc = x86_setup_perfctr(event);
out:
	put_cpu();
	return rc;
}