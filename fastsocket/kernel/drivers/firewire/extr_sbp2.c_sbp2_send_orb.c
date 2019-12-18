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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  low; scalar_t__ high; } ;
struct sbp2_orb {TYPE_2__ pointer; int /*<<< orphan*/  t; int /*<<< orphan*/  kref; int /*<<< orphan*/  link; int /*<<< orphan*/  request_bus; } ;
struct sbp2_logical_unit {int /*<<< orphan*/  orb_list; int /*<<< orphan*/  tgt; } ;
struct fw_device {int /*<<< orphan*/  max_speed; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  complete_transaction ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_send_request (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,struct sbp2_orb*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fw_device* target_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbp2_send_orb(struct sbp2_orb *orb, struct sbp2_logical_unit *lu,
			  int node_id, int generation, u64 offset)
{
	struct fw_device *device = target_device(lu->tgt);
	unsigned long flags;

	orb->pointer.high = 0;
	orb->pointer.low = cpu_to_be32(orb->request_bus);

	spin_lock_irqsave(&device->card->lock, flags);
	list_add_tail(&orb->link, &lu->orb_list);
	spin_unlock_irqrestore(&device->card->lock, flags);

	/* Take a ref for the orb list and for the transaction callback. */
	kref_get(&orb->kref);
	kref_get(&orb->kref);

	fw_send_request(device->card, &orb->t, TCODE_WRITE_BLOCK_REQUEST,
			node_id, generation, device->max_speed, offset,
			&orb->pointer, sizeof(orb->pointer),
			complete_transaction, orb);
}