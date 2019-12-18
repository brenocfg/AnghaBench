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
struct reordering_mpdu {struct reordering_mpdu* next; } ;
struct reordering_list {struct reordering_mpdu* next; scalar_t__ qlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct reordering_list*) ; 

__attribute__((used)) static inline struct reordering_mpdu * ba_dequeue(struct reordering_list *list)
{
	struct reordering_mpdu *mpdu_blk = NULL;

	ASSERT(list);

		if (list->qlen)
		{
			list->qlen--;
			mpdu_blk = list->next;
			if (mpdu_blk)
			{
				list->next = mpdu_blk->next;
				mpdu_blk->next = NULL;
			}
		}
	return mpdu_blk;
}