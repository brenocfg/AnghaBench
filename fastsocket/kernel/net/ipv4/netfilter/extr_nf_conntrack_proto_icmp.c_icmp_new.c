#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valid_new ;
typedef  int u_int8_t ;
struct sk_buff {int dummy; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_7__ {TYPE_1__ icmp; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_3__ dst; } ;
struct TYPE_9__ {TYPE_5__ tuple; } ;

/* Variables and functions */
#define  ICMP_ADDRESS 131 
#define  ICMP_ECHO 130 
#define  ICMP_INFO_REQUEST 129 
#define  ICMP_TIMESTAMP 128 
 int /*<<< orphan*/  nf_ct_dump_tuple_ip (TYPE_5__*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 

__attribute__((used)) static bool icmp_new(struct nf_conn *ct, const struct sk_buff *skb,
		     unsigned int dataoff)
{
	static const u_int8_t valid_new[] = {
		[ICMP_ECHO] = 1,
		[ICMP_TIMESTAMP] = 1,
		[ICMP_INFO_REQUEST] = 1,
		[ICMP_ADDRESS] = 1
	};

	if (ct->tuplehash[0].tuple.dst.u.icmp.type >= sizeof(valid_new)
	    || !valid_new[ct->tuplehash[0].tuple.dst.u.icmp.type]) {
		/* Can't create a new ICMP `conn' with this. */
		pr_debug("icmp: can't create new conn with type %u\n",
			 ct->tuplehash[0].tuple.dst.u.icmp.type);
		nf_ct_dump_tuple_ip(&ct->tuplehash[0].tuple);
		return false;
	}
	return true;
}