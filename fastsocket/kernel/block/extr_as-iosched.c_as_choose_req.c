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
struct request {int dummy; } ;
struct as_data {scalar_t__* last_sector; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ BACK_PENALTY ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAXBACK ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int rq_is_sync (struct request*) ; 

__attribute__((used)) static struct request *
as_choose_req(struct as_data *ad, struct request *rq1, struct request *rq2)
{
	int data_dir;
	sector_t last, s1, s2, d1, d2;
	int r1_wrap=0, r2_wrap=0;	/* requests are behind the disk head */
	const sector_t maxback = MAXBACK;

	if (rq1 == NULL || rq1 == rq2)
		return rq2;
	if (rq2 == NULL)
		return rq1;

	data_dir = rq_is_sync(rq1);

	last = ad->last_sector[data_dir];
	s1 = blk_rq_pos(rq1);
	s2 = blk_rq_pos(rq2);

	BUG_ON(data_dir != rq_is_sync(rq2));

	/*
	 * Strict one way elevator _except_ in the case where we allow
	 * short backward seeks which are biased as twice the cost of a
	 * similar forward seek.
	 */
	if (s1 >= last)
		d1 = s1 - last;
	else if (s1+maxback >= last)
		d1 = (last - s1)*BACK_PENALTY;
	else {
		r1_wrap = 1;
		d1 = 0; /* shut up, gcc */
	}

	if (s2 >= last)
		d2 = s2 - last;
	else if (s2+maxback >= last)
		d2 = (last - s2)*BACK_PENALTY;
	else {
		r2_wrap = 1;
		d2 = 0;
	}

	/* Found required data */
	if (!r1_wrap && r2_wrap)
		return rq1;
	else if (!r2_wrap && r1_wrap)
		return rq2;
	else if (r1_wrap && r2_wrap) {
		/* both behind the head */
		if (s1 <= s2)
			return rq1;
		else
			return rq2;
	}

	/* Both requests in front of the head */
	if (d1 < d2)
		return rq1;
	else if (d2 < d1)
		return rq2;
	else {
		if (s1 >= s2)
			return rq1;
		else
			return rq2;
	}
}