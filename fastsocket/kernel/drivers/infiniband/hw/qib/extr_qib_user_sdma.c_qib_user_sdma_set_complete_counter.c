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
typedef  int /*<<< orphan*/  u32 ;
struct qib_user_sdma_queue {int /*<<< orphan*/  sent_counter; } ;

/* Variables and functions */

__attribute__((used)) static void qib_user_sdma_set_complete_counter(struct qib_user_sdma_queue *pq,
					       u32 c)
{
	pq->sent_counter = c;
}