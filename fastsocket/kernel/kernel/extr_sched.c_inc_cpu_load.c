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
struct rq {int /*<<< orphan*/  load; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_load_add (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void inc_cpu_load(struct rq *rq, unsigned long load)
{
	update_load_add(&rq->load, load);
}