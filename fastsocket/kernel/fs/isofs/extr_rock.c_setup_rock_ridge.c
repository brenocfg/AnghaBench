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
struct rock_state {int len; unsigned char* chr; } ;
struct iso_directory_record {int* name_len; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int s_rock_offset; } ;

/* Variables and functions */
 TYPE_1__* ISOFS_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_rock_ridge(struct iso_directory_record *de,
			struct inode *inode, struct rock_state *rs)
{
	rs->len = sizeof(struct iso_directory_record) + de->name_len[0];
	if (rs->len & 1)
		(rs->len)++;
	rs->chr = (unsigned char *)de + rs->len;
	rs->len = *((unsigned char *)de) - rs->len;
	if (rs->len < 0)
		rs->len = 0;

	if (ISOFS_SB(inode->i_sb)->s_rock_offset != -1) {
		rs->len -= ISOFS_SB(inode->i_sb)->s_rock_offset;
		rs->chr += ISOFS_SB(inode->i_sb)->s_rock_offset;
		if (rs->len < 0)
			rs->len = 0;
	}
}