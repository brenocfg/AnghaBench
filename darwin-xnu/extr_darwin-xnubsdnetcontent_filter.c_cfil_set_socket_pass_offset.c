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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct socket {int dummy; } ;
struct cfi_buf {scalar_t__ cfi_pending_first; scalar_t__ cfi_pending_last; scalar_t__ cfi_pass_offset; } ;
struct cfil_info {int /*<<< orphan*/  cfi_sock_id; struct cfil_entry* cfi_entries; struct cfi_buf cfi_rcv; struct cfi_buf cfi_snd; } ;
struct cfe_buf {scalar_t__ cfe_pass_offset; } ;
struct cfil_entry {struct cfe_buf cfe_rcv; struct cfe_buf cfe_snd; int /*<<< orphan*/ * cfe_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAX_CONTENT_FILTER ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

__attribute__((used)) static int
cfil_set_socket_pass_offset(struct socket *so, struct cfil_info *cfil_info, int outgoing)
{
	struct cfi_buf *cfi_buf;
	struct cfil_entry *entry;
	struct cfe_buf *entrybuf;
	uint32_t kcunit;
	uint64_t pass_offset = 0;

	if (cfil_info == NULL)
		return (0);

	CFIL_LOG(LOG_INFO, "so %llx outgoing %d",
		(uint64_t)VM_KERNEL_ADDRPERM(so), outgoing);

	socket_lock_assert_owned(so);

	if (outgoing)
		cfi_buf = &cfil_info->cfi_snd;
	else
		cfi_buf = &cfil_info->cfi_rcv;

	CFIL_LOG(LOG_DEBUG, "CFIL: <so %llx, sockID %llu> outgoing %d cfi_pending_first %llu cfi_pending_last %llu",
			 (uint64_t)VM_KERNEL_ADDRPERM(so), cfil_info->cfi_sock_id, outgoing,
			 cfi_buf->cfi_pending_first, cfi_buf->cfi_pending_last);

	if (cfi_buf->cfi_pending_last - cfi_buf->cfi_pending_first == 0) {
		for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
			entry = &cfil_info->cfi_entries[kcunit - 1];

			/* Are we attached to a filter? */
			if (entry->cfe_filter == NULL)
				continue;

			if (outgoing)
				entrybuf = &entry->cfe_snd;
			else
				entrybuf = &entry->cfe_rcv;

			if (pass_offset == 0 ||
			    entrybuf->cfe_pass_offset < pass_offset)
				pass_offset = entrybuf->cfe_pass_offset;
		}
		cfi_buf->cfi_pass_offset = pass_offset;
	}

	CFIL_LOG(LOG_DEBUG, "CFIL: <so %llx, sockID %llu>, cfi_pass_offset %llu",
			 (uint64_t)VM_KERNEL_ADDRPERM(so), cfil_info->cfi_sock_id, cfi_buf->cfi_pass_offset);

	return (0);
}