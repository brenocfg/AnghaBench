#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* kq; } ;
typedef  TYPE_2__ kqueue_t ;
struct TYPE_4__ {int kq_state; int /*<<< orphan*/  kq_reqlock; } ;

/* Variables and functions */
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
kq_req_lock(kqueue_t kqu)
{
	assert(kqu.kq->kq_state & (KQ_WORKLOOP | KQ_WORKQ));
	lck_spin_lock(&kqu.kq->kq_reqlock);
}