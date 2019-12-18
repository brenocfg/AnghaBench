#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  unsigned long u32 ;
struct TYPE_4__ {scalar_t__ use_cq; scalar_t__ use_enh_siga; } ;
struct TYPE_5__ {TYPE_1__ out; } ;
struct qdio_q {TYPE_3__* irq_ptr; int /*<<< orphan*/  nr; int /*<<< orphan*/  mask; TYPE_2__ u; } ;
struct TYPE_6__ {unsigned long sch_token; int /*<<< orphan*/  schid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,TYPE_3__*,char*,int,...) ; 
 int /*<<< orphan*/  DBF_WARN ; 
 scalar_t__ QDIO_BUSY_BIT_PATIENCE ; 
 scalar_t__ QDIO_IQDIO_QFMT ; 
 unsigned int QDIO_SIGA_QEBSM_FLAG ; 
 unsigned int QDIO_SIGA_WRITE ; 
 unsigned int QDIO_SIGA_WRITEQ ; 
 int /*<<< orphan*/  SCH_NO (struct qdio_q*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int do_siga_output (unsigned long,int /*<<< orphan*/ ,unsigned int*,unsigned int,unsigned long) ; 
 scalar_t__ get_usecs () ; 
 scalar_t__ is_qebsm (struct qdio_q*) ; 
 scalar_t__ queue_type (struct qdio_q*) ; 

__attribute__((used)) static int qdio_siga_output(struct qdio_q *q, unsigned int *busy_bit,
	unsigned long aob)
{
	unsigned long schid = *((u32 *) &q->irq_ptr->schid);
	unsigned int fc = QDIO_SIGA_WRITE;
	u64 start_time = 0;
	int cc, retries = 0;
	unsigned long laob = 0;

	if (q->u.out.use_enh_siga)
		fc = 3;

	if (q->u.out.use_cq && aob != 0) {
		fc = QDIO_SIGA_WRITEQ;
		laob = aob;
	}

	if (is_qebsm(q)) {
		schid = q->irq_ptr->sch_token;
		fc |= QDIO_SIGA_QEBSM_FLAG;
	}
again:
	WARN_ON_ONCE((aob != 0 && queue_type(q) != QDIO_IQDIO_QFMT) ||
		(aob != 0 && fc != QDIO_SIGA_WRITEQ));
	cc = do_siga_output(schid, q->mask, busy_bit, fc, laob);

	/* hipersocket busy condition */
	if (*busy_bit) {
		WARN_ON(queue_type(q) != QDIO_IQDIO_QFMT || cc != 2);
		retries++;

		if (!start_time) {
			start_time = get_usecs();
			goto again;
		}
		if ((get_usecs() - start_time) < QDIO_BUSY_BIT_PATIENCE)
			goto again;
	}
	if (retries) {
		DBF_DEV_EVENT(DBF_WARN, q->irq_ptr,
			      "%4x cc2 BB1:%1d", SCH_NO(q), q->nr);
		DBF_DEV_EVENT(DBF_WARN, q->irq_ptr, "count:%u", retries);
	}
	return cc;
}