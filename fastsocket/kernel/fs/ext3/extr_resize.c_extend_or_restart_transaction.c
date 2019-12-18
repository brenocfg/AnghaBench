#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct buffer_head {int dummy; } ;
struct TYPE_6__ {int h_buffer_credits; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_MAX_TRANS_DATA ; 
 int ext3_journal_extend (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ext3_journal_get_write_access (TYPE_1__*,struct buffer_head*) ; 
 int ext3_journal_restart (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int extend_or_restart_transaction(handle_t *handle, int thresh,
					 struct buffer_head *bh)
{
	int err;

	if (handle->h_buffer_credits >= thresh)
		return 0;

	err = ext3_journal_extend(handle, EXT3_MAX_TRANS_DATA);
	if (err < 0)
		return err;
	if (err) {
		err = ext3_journal_restart(handle, EXT3_MAX_TRANS_DATA);
		if (err)
			return err;
		err = ext3_journal_get_write_access(handle, bh);
		if (err)
			return err;
	}

	return 0;
}