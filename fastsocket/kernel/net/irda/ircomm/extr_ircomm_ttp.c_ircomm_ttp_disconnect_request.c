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
struct ircomm_info {int dummy; } ;
struct ircomm_cb {int /*<<< orphan*/  tsap; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_NORMAL ; 
 int irttp_disconnect_request (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 

__attribute__((used)) static int ircomm_ttp_disconnect_request(struct ircomm_cb *self,
					 struct sk_buff *userdata,
					 struct ircomm_info *info)
{
	int ret;

	/* Don't forget to refcount it - should be NULL anyway */
	if(userdata)
		skb_get(userdata);

	ret = irttp_disconnect_request(self->tsap, userdata, P_NORMAL);

	return ret;
}