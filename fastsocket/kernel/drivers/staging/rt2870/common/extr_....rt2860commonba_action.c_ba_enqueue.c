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
struct reordering_list {struct reordering_mpdu* next; int /*<<< orphan*/  qlen; } ;

/* Variables and functions */

__attribute__((used)) static inline void ba_enqueue(struct reordering_list *list, struct reordering_mpdu *mpdu_blk)
{
	list->qlen++;
	mpdu_blk->next = list->next;
	list->next = mpdu_blk;
}