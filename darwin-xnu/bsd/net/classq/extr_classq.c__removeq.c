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
typedef  int /*<<< orphan*/  class_queue_t ;

/* Variables and functions */
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _removeq_mbuf (int /*<<< orphan*/ *,void*) ; 
 int qptype (int /*<<< orphan*/ *) ; 

void
_removeq(class_queue_t *q, void *pkt)
{
	switch (qptype(q)) {
	case QP_MBUF:
		_removeq_mbuf(q, pkt);
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}
}