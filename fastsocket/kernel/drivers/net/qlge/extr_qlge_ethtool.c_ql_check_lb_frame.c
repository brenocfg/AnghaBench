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
struct sk_buff {unsigned int len; int* data; } ;
struct ql_adapter {int /*<<< orphan*/  lb_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

void ql_check_lb_frame(struct ql_adapter *qdev,
					struct sk_buff *skb)
{
	unsigned int frame_size = skb->len;

	if ((*(skb->data + 3) == 0xFF) &&
		(*(skb->data + frame_size / 2 + 10) == 0xBE) &&
		(*(skb->data + frame_size / 2 + 12) == 0xAF)) {
			atomic_dec(&qdev->lb_count);
			return;
	}
}