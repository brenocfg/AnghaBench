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
struct defer_queue {int tail; int head; int defer_bits; int* tag; } ;
struct nv_swncq_port_priv {struct defer_queue defer_queue; } ;
struct ata_queued_cmd {int tag; } ;
struct ata_port {struct nv_swncq_port_priv* private_data; } ;

/* Variables and functions */
 int ATA_MAX_QUEUE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void nv_swncq_qc_to_dq(struct ata_port *ap, struct ata_queued_cmd *qc)
{
	struct nv_swncq_port_priv *pp = ap->private_data;
	struct defer_queue *dq = &pp->defer_queue;

	/* queue is full */
	WARN_ON(dq->tail - dq->head == ATA_MAX_QUEUE);
	dq->defer_bits |= (1 << qc->tag);
	dq->tag[dq->tail++ & (ATA_MAX_QUEUE - 1)] = qc->tag;
}