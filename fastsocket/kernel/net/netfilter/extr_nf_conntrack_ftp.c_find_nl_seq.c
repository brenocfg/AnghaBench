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
typedef  scalar_t__ u32 ;
struct nf_ct_ftp_master {unsigned int* seq_aft_nl_num; scalar_t__** seq_aft_nl; } ;

/* Variables and functions */

__attribute__((used)) static int find_nl_seq(u32 seq, const struct nf_ct_ftp_master *info, int dir)
{
	unsigned int i;

	for (i = 0; i < info->seq_aft_nl_num[dir]; i++)
		if (info->seq_aft_nl[dir][i] == seq)
			return 1;
	return 0;
}