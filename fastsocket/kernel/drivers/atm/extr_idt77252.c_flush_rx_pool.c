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
struct rx_pool {scalar_t__ len; int /*<<< orphan*/  queue; } ;
struct idt77252_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
flush_rx_pool(struct idt77252_dev *card, struct rx_pool *rpp)
{
	skb_queue_head_init(&rpp->queue);
	rpp->len = 0;
}