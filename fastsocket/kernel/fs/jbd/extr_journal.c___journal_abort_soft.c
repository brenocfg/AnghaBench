#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int j_flags; int j_errno; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int JFS_ABORT ; 
 int /*<<< orphan*/  __journal_abort_hard (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_update_superblock (TYPE_1__*,int) ; 

__attribute__((used)) static void __journal_abort_soft (journal_t *journal, int errno)
{
	if (journal->j_flags & JFS_ABORT)
		return;

	if (!journal->j_errno)
		journal->j_errno = errno;

	__journal_abort_hard(journal);

	if (errno)
		journal_update_superblock(journal, 1);
}