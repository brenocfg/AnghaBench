#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct journal_head {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  j_blocksize; int /*<<< orphan*/  j_dev; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 struct buffer_head* __getblk (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct journal_head* journal_add_journal_head (struct buffer_head*) ; 
 int journal_next_log_block (TYPE_1__*,unsigned int*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

struct journal_head *journal_get_descriptor_buffer(journal_t *journal)
{
	struct buffer_head *bh;
	unsigned int blocknr;
	int err;

	err = journal_next_log_block(journal, &blocknr);

	if (err)
		return NULL;

	bh = __getblk(journal->j_dev, blocknr, journal->j_blocksize);
	if (!bh)
		return NULL;
	lock_buffer(bh);
	memset(bh->b_data, 0, journal->j_blocksize);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);
	BUFFER_TRACE(bh, "return this buffer");
	return journal_add_journal_head(bh);
}