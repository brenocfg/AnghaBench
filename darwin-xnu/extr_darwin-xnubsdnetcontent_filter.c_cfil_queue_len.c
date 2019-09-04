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
typedef  scalar_t__ uint64_t ;
struct cfil_queue {scalar_t__ q_start; scalar_t__ q_end; } ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t
cfil_queue_len(struct cfil_queue *cfq)
{
	return (cfq->q_end - cfq->q_start);
}