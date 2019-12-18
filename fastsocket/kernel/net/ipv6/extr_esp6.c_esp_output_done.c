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
struct crypto_async_request {struct sk_buff* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmp; } ;

/* Variables and functions */
 TYPE_1__* ESP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_output_resume (struct sk_buff*,int) ; 

__attribute__((used)) static void esp_output_done(struct crypto_async_request *base, int err)
{
	struct sk_buff *skb = base->data;

	kfree(ESP_SKB_CB(skb)->tmp);
	xfrm_output_resume(skb, err);
}