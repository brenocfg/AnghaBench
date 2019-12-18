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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pkt_add_list_last(struct bio *bio, struct bio **list_head, struct bio **list_tail)
{
	bio->bi_next = NULL;
	if (*list_tail) {
		BUG_ON((*list_head) == NULL);
		(*list_tail)->bi_next = bio;
		(*list_tail) = bio;
	} else {
		BUG_ON((*list_head) != NULL);
		(*list_head) = bio;
		(*list_tail) = bio;
	}
}