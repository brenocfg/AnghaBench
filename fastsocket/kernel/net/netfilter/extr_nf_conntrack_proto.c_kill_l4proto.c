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
struct nf_conntrack_l4proto {scalar_t__ l3proto; int /*<<< orphan*/  l4proto; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 scalar_t__ nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_protonum (struct nf_conn*) ; 

__attribute__((used)) static int kill_l4proto(struct nf_conn *i, void *data)
{
	struct nf_conntrack_l4proto *l4proto;
	l4proto = (struct nf_conntrack_l4proto *)data;
	return nf_ct_protonum(i) == l4proto->l4proto &&
	       nf_ct_l3num(i) == l4proto->l3proto;
}