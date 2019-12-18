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
struct request {int /*<<< orphan*/  atomic_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_ATOM_COMPLETE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void blk_clear_rq_complete(struct request *rq)
{
	clear_bit(REQ_ATOM_COMPLETE, &rq->atomic_flags);
}