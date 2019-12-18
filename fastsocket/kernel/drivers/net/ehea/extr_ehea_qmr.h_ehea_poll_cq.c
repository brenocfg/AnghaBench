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
struct ehea_cqe {int dummy; } ;
struct ehea_cq {int /*<<< orphan*/  hw_queue; } ;

/* Variables and functions */
 struct ehea_cqe* hw_qeit_get_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct ehea_cqe *ehea_poll_cq(struct ehea_cq *my_cq)
{
	return hw_qeit_get_valid(&my_cq->hw_queue);
}