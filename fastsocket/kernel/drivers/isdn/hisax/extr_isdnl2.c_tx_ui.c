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
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ui_queue; } ;
struct PStack {TYPE_1__ l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int MAX_HEADER_LEN ; 
 int /*<<< orphan*/  UI ; 
 int /*<<< orphan*/  enqueue_ui (struct PStack*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sethdraddr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void
tx_ui(struct PStack *st)
{
	struct sk_buff *skb;
	u_char header[MAX_HEADER_LEN];
	int i;

	i = sethdraddr(&(st->l2), header, CMD);
	header[i++] = UI;
	while ((skb = skb_dequeue(&st->l2.ui_queue))) {
		memcpy(skb_push(skb, i), header, i);
		enqueue_ui(st, skb);
	}
}