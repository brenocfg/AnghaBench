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
struct irlap_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PI_ADD_BOFS ; 
 int /*<<< orphan*/  PI_BAUD_RATE ; 
 int /*<<< orphan*/  PI_DATA_SIZE ; 
 int /*<<< orphan*/  PI_LINK_DISC ; 
 int /*<<< orphan*/  PI_MAX_TURN_TIME ; 
 int /*<<< orphan*/  PI_MIN_TURN_TIME ; 
 int /*<<< orphan*/  PI_WINDOW_SIZE ; 
 int irda_param_insert (struct irlap_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irlap_param_info ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 

int irlap_insert_qos_negotiation_params(struct irlap_cb *self,
					struct sk_buff *skb)
{
	int ret;

	/* Insert data rate */
	ret = irda_param_insert(self, PI_BAUD_RATE, skb_tail_pointer(skb),
				skb_tailroom(skb), &irlap_param_info);
	if (ret < 0)
		return ret;
	skb_put(skb, ret);

	/* Insert max turnaround time */
	ret = irda_param_insert(self, PI_MAX_TURN_TIME, skb_tail_pointer(skb),
				skb_tailroom(skb), &irlap_param_info);
	if (ret < 0)
		return ret;
	skb_put(skb, ret);

	/* Insert data size */
	ret = irda_param_insert(self, PI_DATA_SIZE, skb_tail_pointer(skb),
				skb_tailroom(skb), &irlap_param_info);
	if (ret < 0)
		return ret;
	skb_put(skb, ret);

	/* Insert window size */
	ret = irda_param_insert(self, PI_WINDOW_SIZE, skb_tail_pointer(skb),
				skb_tailroom(skb), &irlap_param_info);
	if (ret < 0)
		return ret;
	skb_put(skb, ret);

	/* Insert additional BOFs */
	ret = irda_param_insert(self, PI_ADD_BOFS, skb_tail_pointer(skb),
				skb_tailroom(skb), &irlap_param_info);
	if (ret < 0)
		return ret;
	skb_put(skb, ret);

	/* Insert minimum turnaround time */
	ret = irda_param_insert(self, PI_MIN_TURN_TIME, skb_tail_pointer(skb),
				skb_tailroom(skb), &irlap_param_info);
	if (ret < 0)
		return ret;
	skb_put(skb, ret);

	/* Insert link disconnect/threshold time */
	ret = irda_param_insert(self, PI_LINK_DISC, skb_tail_pointer(skb),
				skb_tailroom(skb), &irlap_param_info);
	if (ret < 0)
		return ret;
	skb_put(skb, ret);

	return 0;
}