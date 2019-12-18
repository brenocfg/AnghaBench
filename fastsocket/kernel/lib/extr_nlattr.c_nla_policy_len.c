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
struct nla_policy {size_t type; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__* nla_attr_minlen ; 
 scalar_t__ nla_total_size (scalar_t__) ; 

int
nla_policy_len(const struct nla_policy *p, int n)
{
	int i, len = 0;

	for (i = 0; i < n; i++) {
		if (p->len)
			len += nla_total_size(p->len);
		else if (nla_attr_minlen[p->type])
			len += nla_total_size(nla_attr_minlen[p->type]);
	}

	return len;
}