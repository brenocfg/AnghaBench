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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ccid {TYPE_1__* ccid_ops; } ;
struct TYPE_2__ {int (* ccid_hc_tx_send_packet ) (struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static inline int ccid_hc_tx_send_packet(struct ccid *ccid, struct sock *sk,
					 struct sk_buff *skb)
{
	int rc = 0;
	if (ccid->ccid_ops->ccid_hc_tx_send_packet != NULL)
		rc = ccid->ccid_ops->ccid_hc_tx_send_packet(sk, skb);
	return rc;
}