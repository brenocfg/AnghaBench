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
struct t4_cqe {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_fw6_msg {int /*<<< orphan*/ * data; } ;
struct c4iw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_ev_dispatch (struct c4iw_dev*,struct t4_cqe*) ; 
 struct cpl_fw6_msg* cplhdr (struct sk_buff*) ; 

__attribute__((used)) static int async_event(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct cpl_fw6_msg *rpl = cplhdr(skb);
	c4iw_ev_dispatch(dev, (struct t4_cqe *)&rpl->data[0]);
	return 0;
}