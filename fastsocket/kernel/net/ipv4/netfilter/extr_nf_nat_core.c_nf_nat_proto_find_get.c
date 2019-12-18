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
typedef  int /*<<< orphan*/  u_int8_t ;
struct nf_nat_protocol {int /*<<< orphan*/  me; } ;

/* Variables and functions */
 struct nf_nat_protocol* __nf_nat_proto_find (int /*<<< orphan*/ ) ; 
 struct nf_nat_protocol nf_nat_unknown_protocol ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

const struct nf_nat_protocol *
nf_nat_proto_find_get(u_int8_t protonum)
{
	const struct nf_nat_protocol *p;

	rcu_read_lock();
	p = __nf_nat_proto_find(protonum);
	if (!try_module_get(p->me))
		p = &nf_nat_unknown_protocol;
	rcu_read_unlock();

	return p;
}