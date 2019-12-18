#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  stream_timeout; } ;
struct TYPE_6__ {TYPE_2__ gre; } ;
struct nf_conn {TYPE_3__ proto; TYPE_1__* tuplehash; } ;
struct TYPE_4__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRE_STREAM_TIMEOUT ; 
 int /*<<< orphan*/  GRE_TIMEOUT ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static bool gre_new(struct nf_conn *ct, const struct sk_buff *skb,
		    unsigned int dataoff)
{
	pr_debug(": ");
	nf_ct_dump_tuple(&ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);

	/* initialize to sane value.  Ideally a conntrack helper
	 * (e.g. in case of pptp) is increasing them */
	ct->proto.gre.stream_timeout = GRE_STREAM_TIMEOUT;
	ct->proto.gre.timeout = GRE_TIMEOUT;

	return true;
}