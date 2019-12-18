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
struct sk_buff {int dummy; } ;
struct pppoatm_vcc {int /*<<< orphan*/  wakeup_tasklet; int /*<<< orphan*/  (* old_pop ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 struct pppoatm_vcc* atmvcc_to_pvcc (struct atm_vcc*) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppoatm_pop(struct atm_vcc *atmvcc, struct sk_buff *skb)
{
	struct pppoatm_vcc *pvcc = atmvcc_to_pvcc(atmvcc);
	pvcc->old_pop(atmvcc, skb);
	/*
	 * We don't really always want to do this since it's
	 * really inefficient - it would be much better if we could
	 * test if we had actually throttled the generic layer.
	 * Unfortunately then there would be a nasty SMP race where
	 * we could clear that flag just as we refuse another packet.
	 * For now we do the safe thing.
	 */
	tasklet_schedule(&pvcc->wakeup_tasklet);
}