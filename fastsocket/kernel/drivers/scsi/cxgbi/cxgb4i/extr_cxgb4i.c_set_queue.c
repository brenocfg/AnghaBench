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
struct sk_buff {unsigned int queue_mapping; } ;
struct cxgbi_sock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void set_queue(struct sk_buff *skb, unsigned int queue,
				const struct cxgbi_sock *csk)
{
	skb->queue_mapping = queue;
}