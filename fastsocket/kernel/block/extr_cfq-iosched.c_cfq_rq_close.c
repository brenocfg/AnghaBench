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
struct cfq_queue {int dummy; } ;
struct cfq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFQQ_CLOSE_THR ; 
 scalar_t__ cfq_dist_from_last (struct cfq_data*,struct request*) ; 

__attribute__((used)) static inline int cfq_rq_close(struct cfq_data *cfqd, struct cfq_queue *cfqq,
			       struct request *rq)
{
	return cfq_dist_from_last(cfqd, rq) <= CFQQ_CLOSE_THR;
}