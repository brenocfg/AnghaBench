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
struct phonet_protocol {TYPE_1__* prot; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 unsigned int PHONET_NPROTO ; 
 struct phonet_protocol** proto_tab ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct phonet_protocol *phonet_proto_get(unsigned int protocol)
{
	struct phonet_protocol *pp;

	if (protocol >= PHONET_NPROTO)
		return NULL;

	rcu_read_lock();
	pp = proto_tab[protocol];
	if (pp && !try_module_get(pp->prot->owner))
		pp = NULL;
	rcu_read_unlock();

	return pp;
}