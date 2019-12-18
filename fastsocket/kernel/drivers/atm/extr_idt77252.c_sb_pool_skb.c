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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct idt77252_dev {TYPE_1__* sbpool; } ;
struct TYPE_2__ {struct sk_buff** skb; } ;

/* Variables and functions */
 int FBQ_SIZE ; 
 unsigned int POOL_INDEX (int /*<<< orphan*/ ) ; 
 unsigned int POOL_QUEUE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
sb_pool_skb(struct idt77252_dev *card, u32 handle)
{
	unsigned int queue, index;

	queue = POOL_QUEUE(handle);
	if (queue > 3)
		return NULL;

	index = POOL_INDEX(handle);
	if (index > FBQ_SIZE - 1)
		return NULL;

	return card->sbpool[queue].skb[index];
}