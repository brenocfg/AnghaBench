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
typedef  union c2wr {int dummy; } c2wr ;
typedef  int /*<<< orphan*/  u32 ;
struct c2_qp {int dummy; } ;
struct c2_mq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ c2wr_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCERR_PENDING ; 
 int /*<<< orphan*/  CCWR_MAGIC ; 
 int EINVAL ; 
 union c2wr* c2_mq_alloc (struct c2_mq*) ; 
 int /*<<< orphan*/  c2_mq_produce (struct c2_mq*) ; 
 int /*<<< orphan*/  c2_wr_set_result (union c2wr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qp_wr_post(struct c2_mq *q, union c2wr * wr, struct c2_qp *qp, u32 size)
{
	union c2wr *msg;

	msg = c2_mq_alloc(q);
	if (msg == NULL) {
		return -EINVAL;
	}
#ifdef CCMSGMAGIC
	((c2wr_hdr_t *) wr)->magic = cpu_to_be32(CCWR_MAGIC);
#endif

	/*
	 * Since all header fields in the WR are the same as the
	 * CQE, set the following so the adapter need not.
	 */
	c2_wr_set_result(wr, CCERR_PENDING);

	/*
	 * Copy the wr down to the adapter
	 */
	memcpy((void *) msg, (void *) wr, size);

	c2_mq_produce(q);
	return 0;
}