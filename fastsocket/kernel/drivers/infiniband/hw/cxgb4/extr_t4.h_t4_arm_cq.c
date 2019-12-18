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
typedef  int u32 ;
struct t4_cq {scalar_t__ cidx_inc; int /*<<< orphan*/  gts; int /*<<< orphan*/  cqid; } ;

/* Variables and functions */
 int CIDXINC (scalar_t__) ; 
 scalar_t__ CIDXINC_MASK ; 
 int INGRESSQID (int /*<<< orphan*/ ) ; 
 int SEINTARM (int) ; 
 int TIMERREG (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int t4_arm_cq(struct t4_cq *cq, int se)
{
	u32 val;

	while (cq->cidx_inc > CIDXINC_MASK) {
		val = SEINTARM(0) | CIDXINC(CIDXINC_MASK) | TIMERREG(7) |
		      INGRESSQID(cq->cqid);
		writel(val, cq->gts);
		cq->cidx_inc -= CIDXINC_MASK;
	}
	val = SEINTARM(se) | CIDXINC(cq->cidx_inc) | TIMERREG(6) |
	      INGRESSQID(cq->cqid);
	writel(val, cq->gts);
	cq->cidx_inc = 0;
	return 0;
}