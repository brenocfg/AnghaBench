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
struct ipz_queue {int toggle_state; } ;
struct ehca_cqe {int cqe_flags; } ;

/* Variables and functions */
 struct ehca_cqe* ipz_qeit_get (struct ipz_queue*) ; 

__attribute__((used)) static inline int ipz_qeit_is_valid(struct ipz_queue *queue)
{
	struct ehca_cqe *cqe = ipz_qeit_get(queue);
	return ((cqe->cqe_flags >> 7) == (queue->toggle_state & 1));
}