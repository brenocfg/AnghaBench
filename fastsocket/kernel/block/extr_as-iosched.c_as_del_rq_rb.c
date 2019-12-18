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
struct as_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_RB_ROOT (struct as_data*,struct request*) ; 
 int /*<<< orphan*/  elv_rb_del (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static inline void as_del_rq_rb(struct as_data *ad, struct request *rq)
{
	elv_rb_del(RQ_RB_ROOT(ad, rq), rq);
}