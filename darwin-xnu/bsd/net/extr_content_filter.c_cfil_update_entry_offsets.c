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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct socket {int dummy; } ;
struct cfil_info {struct cfil_entry* cfi_entries; } ;
struct TYPE_4__ {unsigned int q_start; unsigned int q_end; } ;
struct TYPE_3__ {unsigned int q_start; unsigned int q_end; } ;
struct cfe_buf {scalar_t__ cfe_pass_offset; scalar_t__ cfe_peeked; scalar_t__ cfe_peek_offset; TYPE_2__ cfe_pending_q; TYPE_1__ cfe_ctl_q; } ;
struct cfil_entry {struct cfe_buf cfe_rcv; struct cfe_buf cfe_snd; int /*<<< orphan*/ * cfe_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_INFO_VERIFY (struct cfil_info*) ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAX_CONTENT_FILTER ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 

__attribute__((used)) static int
cfil_update_entry_offsets(struct socket *so, struct cfil_info *cfil_info, int outgoing, unsigned int datalen)
{
	struct cfil_entry *entry;
	struct cfe_buf *entrybuf;
	uint32_t kcunit;

	CFIL_LOG(LOG_INFO, "so %llx outgoing %d datalen %u",
		(uint64_t)VM_KERNEL_ADDRPERM(so), outgoing, datalen);

	for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
		entry = &cfil_info->cfi_entries[kcunit - 1];

		/* Are we attached to the filter? */
		if (entry->cfe_filter == NULL)
			continue;

		if (outgoing)
			entrybuf = &entry->cfe_snd;
		else
			entrybuf = &entry->cfe_rcv;

		entrybuf->cfe_ctl_q.q_start += datalen;
		entrybuf->cfe_pass_offset = entrybuf->cfe_ctl_q.q_start;
		entrybuf->cfe_peeked = entrybuf->cfe_ctl_q.q_start;
		if (entrybuf->cfe_peek_offset < entrybuf->cfe_pass_offset)
			entrybuf->cfe_peek_offset = entrybuf->cfe_pass_offset;

		entrybuf->cfe_ctl_q.q_end += datalen;

		entrybuf->cfe_pending_q.q_start += datalen;
		entrybuf->cfe_pending_q.q_end += datalen;
	}
	CFIL_INFO_VERIFY(cfil_info);
	return (0);
}