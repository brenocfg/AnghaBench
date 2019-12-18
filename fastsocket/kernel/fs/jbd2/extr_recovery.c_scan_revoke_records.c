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
typedef  TYPE_1__ jbd2_journal_revoke_header_t ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  JBD2_FEATURE_INCOMPAT_64BIT ; 
 scalar_t__ JBD2_HAS_INCOMPAT_FEATURE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int jbd2_journal_set_revoke (int /*<<< orphan*/ *,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scan_revoke_records(journal_t *journal, struct buffer_head *bh,
			       tid_t sequence, struct recovery_info *info)
{
	jbd2_journal_revoke_header_t *header;
	int offset, max;
	int record_len = 4;

	header = (jbd2_journal_revoke_header_t *) bh->b_data;
	offset = sizeof(jbd2_journal_revoke_header_t);
	max = be32_to_cpu(header->r_count);

	if (JBD2_HAS_INCOMPAT_FEATURE(journal, JBD2_FEATURE_INCOMPAT_64BIT))
		record_len = 8;

	while (offset + record_len <= max) {
		unsigned long long blocknr;
		int err;

		if (record_len == 4)
			blocknr = be32_to_cpu(* ((__be32 *) (bh->b_data+offset)));
		else
			blocknr = be64_to_cpu(* ((__be64 *) (bh->b_data+offset)));
		offset += record_len;
		err = jbd2_journal_set_revoke(journal, blocknr, sequence);
		if (err)
			return err;
		++info->nr_revokes;
	}
	return 0;
}