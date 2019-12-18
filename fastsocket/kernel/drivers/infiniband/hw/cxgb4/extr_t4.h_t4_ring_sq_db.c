#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  qid; } ;
struct t4_wq {int /*<<< orphan*/  db; TYPE_1__ sq; } ;

/* Variables and functions */
 int PIDX (int /*<<< orphan*/ ) ; 
 int QID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void t4_ring_sq_db(struct t4_wq *wq, u16 inc)
{
	wmb();
	writel(QID(wq->sq.qid) | PIDX(inc), wq->db);
}