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
struct qdio_irq {int /*<<< orphan*/  output_qs; int /*<<< orphan*/  input_qs; TYPE_1__* qdr; int /*<<< orphan*/  qib; } ;
struct qdio_initialize {int no_input_qs; int no_output_qs; int /*<<< orphan*/  qdr_ac; int /*<<< orphan*/  q_format; } ;
struct qdesfmt0 {int dummy; } ;
struct TYPE_2__ {int iqdcnt; int oqdcnt; int iqdsz; int oqdsz; unsigned long qiba; int /*<<< orphan*/  qkey; int /*<<< orphan*/  ac; int /*<<< orphan*/  qfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_DEFAULT_KEY ; 
 int /*<<< orphan*/  __qdio_allocate_fill_qdr (struct qdio_irq*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void setup_qdr(struct qdio_irq *irq_ptr,
		      struct qdio_initialize *qdio_init)
{
	int i;

	irq_ptr->qdr->qfmt = qdio_init->q_format;
	irq_ptr->qdr->ac = qdio_init->qdr_ac;
	irq_ptr->qdr->iqdcnt = qdio_init->no_input_qs;
	irq_ptr->qdr->oqdcnt = qdio_init->no_output_qs;
	irq_ptr->qdr->iqdsz = sizeof(struct qdesfmt0) / 4; /* size in words */
	irq_ptr->qdr->oqdsz = sizeof(struct qdesfmt0) / 4;
	irq_ptr->qdr->qiba = (unsigned long)&irq_ptr->qib;
	irq_ptr->qdr->qkey = PAGE_DEFAULT_KEY;

	for (i = 0; i < qdio_init->no_input_qs; i++)
		__qdio_allocate_fill_qdr(irq_ptr, irq_ptr->input_qs, i, 0);

	for (i = 0; i < qdio_init->no_output_qs; i++)
		__qdio_allocate_fill_qdr(irq_ptr, irq_ptr->output_qs, i,
					 qdio_init->no_input_qs);
}