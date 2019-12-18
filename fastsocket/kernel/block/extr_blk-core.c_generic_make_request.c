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
struct bio {struct bio* bi_next; } ;
struct TYPE_2__ {struct bio** bio_tail; struct bio* bio_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct bio*) ; 
 int /*<<< orphan*/  __generic_make_request (struct bio*) ; 
 TYPE_1__* current ; 

void generic_make_request(struct bio *bio)
{
	if (current->bio_tail) {
		/* make_request is active */
		*(current->bio_tail) = bio;
		bio->bi_next = NULL;
		current->bio_tail = &bio->bi_next;
		return;
	}
	/* following loop may be a bit non-obvious, and so deserves some
	 * explanation.
	 * Before entering the loop, bio->bi_next is NULL (as all callers
	 * ensure that) so we have a list with a single bio.
	 * We pretend that we have just taken it off a longer list, so
	 * we assign bio_list to the next (which is NULL) and bio_tail
	 * to &bio_list, thus initialising the bio_list of new bios to be
	 * added.  __generic_make_request may indeed add some more bios
	 * through a recursive call to generic_make_request.  If it
	 * did, we find a non-NULL value in bio_list and re-enter the loop
	 * from the top.  In this case we really did just take the bio
	 * of the top of the list (no pretending) and so fixup bio_list and
	 * bio_tail or bi_next, and call into __generic_make_request again.
	 *
	 * The loop was structured like this to make only one call to
	 * __generic_make_request (which is important as it is large and
	 * inlined) and to keep the structure simple.
	 */
	BUG_ON(bio->bi_next);
	do {
		current->bio_list = bio->bi_next;
		if (bio->bi_next == NULL)
			current->bio_tail = &current->bio_list;
		else
			bio->bi_next = NULL;
		__generic_make_request(bio);
		bio = current->bio_list;
	} while (bio);
	current->bio_tail = NULL; /* deactivate */
}