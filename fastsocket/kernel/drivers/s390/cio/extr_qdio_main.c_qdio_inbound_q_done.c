#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ timestamp; } ;
struct TYPE_4__ {TYPE_1__ in; } ;
struct qdio_q {int /*<<< orphan*/  first_to_check; int /*<<< orphan*/  irq_ptr; TYPE_2__ u; int /*<<< orphan*/  nr_buf_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 scalar_t__ MACHINE_IS_VM ; 
 scalar_t__ QDIO_INPUT_THRESHOLD ; 
 unsigned char SLSB_P_INPUT_ERROR ; 
 unsigned char SLSB_P_INPUT_PRIMED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_buf_state (struct qdio_q*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_usecs () ; 
 scalar_t__ is_thinint_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 

__attribute__((used)) static inline int qdio_inbound_q_done(struct qdio_q *q)
{
	unsigned char state = 0;

	if (!atomic_read(&q->nr_buf_used))
		return 1;

	qdio_siga_sync_q(q);
	get_buf_state(q, q->first_to_check, &state, 0);

	if (state == SLSB_P_INPUT_PRIMED || state == SLSB_P_INPUT_ERROR)
		/* more work coming */
		return 0;

	if (is_thinint_irq(q->irq_ptr))
		return 1;

	/* don't poll under z/VM */
	if (MACHINE_IS_VM)
		return 1;

	/*
	 * At this point we know, that inbound first_to_check
	 * has (probably) not moved (see qdio_inbound_processing).
	 */
	if (get_usecs() > q->u.in.timestamp + QDIO_INPUT_THRESHOLD) {
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "in done:%02x",
			      q->first_to_check);
		return 1;
	} else
		return 0;
}