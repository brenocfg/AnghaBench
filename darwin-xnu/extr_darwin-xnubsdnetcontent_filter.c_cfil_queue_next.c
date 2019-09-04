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
struct cfil_queue {int dummy; } ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBUFQ_NEXT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mbuf_t
cfil_queue_next(struct cfil_queue *cfq, mbuf_t m)
{
#pragma unused(cfq)
	return (MBUFQ_NEXT(m));
}