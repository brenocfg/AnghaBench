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
typedef  size_t u_int8_t ;
struct nf_nat_protocol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nf_nat_protos ; 
 struct nf_nat_protocol const* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const struct nf_nat_protocol *
__nf_nat_proto_find(u_int8_t protonum)
{
	return rcu_dereference(nf_nat_protos[protonum]);
}