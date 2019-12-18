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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  instance; int /*<<< orphan*/  (* data_indication ) (int /*<<< orphan*/ ,struct lsap_cb*,struct sk_buff*) ;} ;
struct lsap_cb {TYPE_1__ notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  LMP_HEADER ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct lsap_cb*,struct sk_buff*) ; 

void irlmp_data_indication(struct lsap_cb *self, struct sk_buff *skb)
{
	/* Hide LMP header from layer above */
	skb_pull(skb, LMP_HEADER);

	if (self->notify.data_indication) {
		/* Don't forget to refcount it - see irlap_driver_rcv(). */
		skb_get(skb);
		self->notify.data_indication(self->notify.instance, self, skb);
	}
}