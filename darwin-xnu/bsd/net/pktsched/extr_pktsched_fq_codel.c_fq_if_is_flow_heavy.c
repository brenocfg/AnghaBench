#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fq_bytes; } ;
typedef  TYPE_1__ fq_t ;
struct TYPE_7__ {TYPE_1__* fqs_large_flow; } ;
typedef  TYPE_2__ fq_if_t ;

/* Variables and functions */
 scalar_t__ FQ_IF_LARGE_FLOW_BYTE_LIMIT ; 
 int /*<<< orphan*/  fq_empty (TYPE_1__*) ; 

inline void
fq_if_is_flow_heavy(fq_if_t *fqs, fq_t *fq)
{
	fq_t *prev_fq;

	if (fqs->fqs_large_flow != NULL &&
	    fqs->fqs_large_flow->fq_bytes < FQ_IF_LARGE_FLOW_BYTE_LIMIT)
		fqs->fqs_large_flow = NULL;

	if (fq == NULL || fq->fq_bytes < FQ_IF_LARGE_FLOW_BYTE_LIMIT)
		return;

	prev_fq = fqs->fqs_large_flow;
	if (prev_fq == NULL) {
		if (!fq_empty(fq))
			fqs->fqs_large_flow = fq;
		return;
	} else if (fq->fq_bytes > prev_fq->fq_bytes) {
		fqs->fqs_large_flow = fq;
	}
}