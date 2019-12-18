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
struct cfq_data {scalar_t__ last_position; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ blk_rq_pos (struct request*) ; 

__attribute__((used)) static inline sector_t cfq_dist_from_last(struct cfq_data *cfqd,
					  struct request *rq)
{
	if (blk_rq_pos(rq) >= cfqd->last_position)
		return blk_rq_pos(rq) - cfqd->last_position;
	else
		return cfqd->last_position - blk_rq_pos(rq);
}