#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  t_tid; } ;
typedef  TYPE_1__ transaction_t ;
struct journal_head {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_9__ {int j_flags; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_10__ {void* h_sequence; void* h_blocktype; void* h_magic; } ;
typedef  TYPE_3__ journal_header_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int JFS_BARRIER ; 
 int /*<<< orphan*/  JFS_COMMIT_BLOCK ; 
 int /*<<< orphan*/  JFS_MAGIC_NUMBER ; 
 int WRITE_FLUSH_FUA ; 
 int WRITE_SYNC ; 
 int __sync_dirty_buffer (struct buffer_head*,int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_journal_aborted (TYPE_2__*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 struct journal_head* journal_get_descriptor_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  journal_put_journal_head (struct journal_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static int journal_write_commit_record(journal_t *journal,
					transaction_t *commit_transaction)
{
	struct journal_head *descriptor;
	struct buffer_head *bh;
	journal_header_t *header;
	int ret;

	if (is_journal_aborted(journal))
		return 0;

	descriptor = journal_get_descriptor_buffer(journal);
	if (!descriptor)
		return 1;

	bh = jh2bh(descriptor);

	header = (journal_header_t *)(bh->b_data);
	header->h_magic = cpu_to_be32(JFS_MAGIC_NUMBER);
	header->h_blocktype = cpu_to_be32(JFS_COMMIT_BLOCK);
	header->h_sequence = cpu_to_be32(commit_transaction->t_tid);

	JBUFFER_TRACE(descriptor, "write commit block");
	set_buffer_dirty(bh);

	if (journal->j_flags & JFS_BARRIER)
		ret = __sync_dirty_buffer(bh, WRITE_SYNC | WRITE_FLUSH_FUA);
	else
		ret = sync_dirty_buffer(bh);

	put_bh(bh);		/* One for getblk() */
	journal_put_journal_head(descriptor);

	return (ret == -EIO);
}