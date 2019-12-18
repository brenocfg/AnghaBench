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
struct rds_info_message {int /*<<< orphan*/  fport; int /*<<< orphan*/  lport; void* faddr; void* laddr; int /*<<< orphan*/  len; int /*<<< orphan*/  seq; } ;
struct rds_info_iterator {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_dport; int /*<<< orphan*/  h_sport; int /*<<< orphan*/  h_len; int /*<<< orphan*/  h_sequence; } ;
struct rds_incoming {TYPE_1__ i_hdr; } ;
typedef  int /*<<< orphan*/  minfo ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_info_copy (struct rds_info_iterator*,struct rds_info_message*,int) ; 

void rds_inc_info_copy(struct rds_incoming *inc,
		       struct rds_info_iterator *iter,
		       __be32 saddr, __be32 daddr, int flip)
{
	struct rds_info_message minfo;

	minfo.seq = be64_to_cpu(inc->i_hdr.h_sequence);
	minfo.len = be32_to_cpu(inc->i_hdr.h_len);

	if (flip) {
		minfo.laddr = daddr;
		minfo.faddr = saddr;
		minfo.lport = inc->i_hdr.h_dport;
		minfo.fport = inc->i_hdr.h_sport;
	} else {
		minfo.laddr = saddr;
		minfo.faddr = daddr;
		minfo.lport = inc->i_hdr.h_sport;
		minfo.fport = inc->i_hdr.h_dport;
	}

	rds_info_copy(iter, &minfo, sizeof(minfo));
}