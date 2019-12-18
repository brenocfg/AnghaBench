#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  t_tid; } ;
typedef  TYPE_1__ transaction_t ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct journal_head {int dummy; } ;
struct commit_header {void** h_chksum; int /*<<< orphan*/  h_chksum_size; int /*<<< orphan*/  h_chksum_type; void* h_commit_nsec; int /*<<< orphan*/  h_commit_sec; void* h_sequence; void* h_blocktype; void* h_magic; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; scalar_t__ b_data; } ;
struct TYPE_10__ {int j_flags; } ;
typedef  TYPE_2__ journal_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int JBD2_BARRIER ; 
 int /*<<< orphan*/  JBD2_COMMIT_BLOCK ; 
 int /*<<< orphan*/  JBD2_CRC32_CHKSUM ; 
 int /*<<< orphan*/  JBD2_CRC32_CHKSUM_SIZE ; 
 int /*<<< orphan*/  JBD2_FEATURE_COMPAT_CHECKSUM ; 
 int /*<<< orphan*/  JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT ; 
 scalar_t__ JBD2_HAS_COMPAT_FEATURE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JBD2_HAS_INCOMPAT_FEATURE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JBD2_MAGIC_NUMBER ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int WRITE_FLUSH_FUA ; 
 int WRITE_SYNC_PLUG ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct timespec current_kernel_time () ; 
 scalar_t__ is_journal_aborted (TYPE_2__*) ; 
 struct journal_head* jbd2_journal_get_descriptor_buffer (TYPE_2__*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  journal_end_buffer_io_sync ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int submit_bh (int,struct buffer_head*) ; 

__attribute__((used)) static int journal_submit_commit_record(journal_t *journal,
					transaction_t *commit_transaction,
					struct buffer_head **cbh,
					__u32 crc32_sum)
{
	struct journal_head *descriptor;
	struct commit_header *tmp;
	struct buffer_head *bh;
	int ret;
	struct timespec now = current_kernel_time();

	if (is_journal_aborted(journal))
		return 0;

	descriptor = jbd2_journal_get_descriptor_buffer(journal);
	if (!descriptor)
		return 1;

	bh = jh2bh(descriptor);

	tmp = (struct commit_header *)bh->b_data;
	tmp->h_magic = cpu_to_be32(JBD2_MAGIC_NUMBER);
	tmp->h_blocktype = cpu_to_be32(JBD2_COMMIT_BLOCK);
	tmp->h_sequence = cpu_to_be32(commit_transaction->t_tid);
	tmp->h_commit_sec = cpu_to_be64(now.tv_sec);
	tmp->h_commit_nsec = cpu_to_be32(now.tv_nsec);

	if (JBD2_HAS_COMPAT_FEATURE(journal,
				    JBD2_FEATURE_COMPAT_CHECKSUM)) {
		tmp->h_chksum_type 	= JBD2_CRC32_CHKSUM;
		tmp->h_chksum_size 	= JBD2_CRC32_CHKSUM_SIZE;
		tmp->h_chksum[0] 	= cpu_to_be32(crc32_sum);
	}

	JBUFFER_TRACE(descriptor, "submit commit block");
	lock_buffer(bh);
	clear_buffer_dirty(bh);
	set_buffer_uptodate(bh);
	bh->b_end_io = journal_end_buffer_io_sync;

	if (journal->j_flags & JBD2_BARRIER &&
	    !JBD2_HAS_INCOMPAT_FEATURE(journal,
				       JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT))
		ret = submit_bh(WRITE_SYNC_PLUG | WRITE_FLUSH_FUA, bh);
	else
		ret = submit_bh(WRITE_SYNC_PLUG, bh);

	*cbh = bh;
	return ret;
}