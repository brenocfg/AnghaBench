#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct chain_len_stats {int /*<<< orphan*/  cls_five_or_more; int /*<<< orphan*/  cls_four; int /*<<< orphan*/  cls_three; int /*<<< orphan*/  cls_two; int /*<<< orphan*/  cls_one; } ;
typedef  TYPE_1__* mbuf_t ;
struct TYPE_3__ {struct TYPE_3__* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
dlil_count_chain_len(mbuf_t m, struct chain_len_stats *cls)
{
	mbuf_t	n = m;
	int chainlen = 0;

	while (n != NULL) {
		chainlen++;
		n = n->m_next;
	}
	switch (chainlen) {
		case 0:
			break;
		case 1:
			atomic_add_64(&cls->cls_one, 1);
			break;
		case 2:
			atomic_add_64(&cls->cls_two, 1);
			break;
		case 3:
			atomic_add_64(&cls->cls_three, 1);
			break;
		case 4:
			atomic_add_64(&cls->cls_four, 1);
			break;
		case 5:
		default:
			atomic_add_64(&cls->cls_five_or_more, 1);
			break;
	}
}