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
struct bio {struct bio* bi_next; } ;

/* Variables and functions */

__attribute__((used)) static inline struct bio *pkt_get_list_first(struct bio **list_head, struct bio **list_tail)
{
	struct bio *bio;

	if (*list_head == NULL)
		return NULL;

	bio = *list_head;
	*list_head = bio->bi_next;
	if (*list_head == NULL)
		*list_tail = NULL;

	bio->bi_next = NULL;
	return bio;
}