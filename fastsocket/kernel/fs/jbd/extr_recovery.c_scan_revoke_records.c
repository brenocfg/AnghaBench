#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct recovery_info {int /*<<< orphan*/  nr_revokes; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  r_count; } ;
typedef  TYPE_1__ journal_revoke_header_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int journal_set_revoke (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scan_revoke_records(journal_t *journal, struct buffer_head *bh,
			       tid_t sequence, struct recovery_info *info)
{
	journal_revoke_header_t *header;
	int offset, max;

	header = (journal_revoke_header_t *) bh->b_data;
	offset = sizeof(journal_revoke_header_t);
	max = be32_to_cpu(header->r_count);

	while (offset < max) {
		unsigned int blocknr;
		int err;

		blocknr = be32_to_cpu(* ((__be32 *) (bh->b_data+offset)));
		offset += 4;
		err = journal_set_revoke(journal, blocknr, sequence);
		if (err)
			return err;
		++info->nr_revokes;
	}
	return 0;
}