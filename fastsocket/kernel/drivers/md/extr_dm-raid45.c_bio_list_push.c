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
struct bio_list {struct bio* tail; struct bio* head; } ;
struct bio {struct bio* bi_next; } ;

/* Variables and functions */

__attribute__((used)) static inline void bio_list_push(struct bio_list *bl, struct bio *bio)
{
	bio->bi_next = bl->head;
	bl->head = bio;

	if (!bl->tail)
		bl->tail = bio;
}