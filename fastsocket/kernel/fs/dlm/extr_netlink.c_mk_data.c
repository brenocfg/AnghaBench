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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct dlm_lock_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_TYPE_LOCK ; 
 struct dlm_lock_data* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dlm_lock_data *mk_data(struct sk_buff *skb)
{
	struct nlattr *ret;

	ret = nla_reserve(skb, DLM_TYPE_LOCK, sizeof(struct dlm_lock_data));
	if (!ret)
		return NULL;
	return nla_data(ret);
}