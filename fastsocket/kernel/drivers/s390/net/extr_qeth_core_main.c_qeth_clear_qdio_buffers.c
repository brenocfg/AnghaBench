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
struct TYPE_2__ {int no_out_queues; scalar_t__* out_qs; } ;
struct qeth_card {TYPE_1__ qdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  qeth_clear_outq_buffers (scalar_t__,int /*<<< orphan*/ ) ; 

void qeth_clear_qdio_buffers(struct qeth_card *card)
{
	int i;

	QETH_DBF_TEXT(TRACE, 2, "clearqdbf");
	/* clear outbound buffers to free skbs */
	for (i = 0; i < card->qdio.no_out_queues; ++i)
		if (card->qdio.out_qs[i])
			qeth_clear_outq_buffers(card->qdio.out_qs[i], 0);
}