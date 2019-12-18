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
typedef  int /*<<< orphan*/  u32 ;
struct work_struct {int dummy; } ;
struct asd_sas_phy {int /*<<< orphan*/  port; int /*<<< orphan*/  sas_prim_lock; int /*<<< orphan*/  sas_prim; int /*<<< orphan*/  port_events_pending; } ;
struct asd_sas_event {struct asd_sas_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_REVALIDATE_DOMAIN ; 
 int /*<<< orphan*/  PORTE_BROADCAST_RCVD ; 
 int /*<<< orphan*/  SAS_DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_discover_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct asd_sas_event* to_asd_sas_event (struct work_struct*) ; 

void sas_porte_broadcast_rcvd(struct work_struct *work)
{
	struct asd_sas_event *ev = to_asd_sas_event(work);
	struct asd_sas_phy *phy = ev->phy;
	unsigned long flags;
	u32 prim;

	clear_bit(PORTE_BROADCAST_RCVD, &phy->port_events_pending);

	spin_lock_irqsave(&phy->sas_prim_lock, flags);
	prim = phy->sas_prim;
	spin_unlock_irqrestore(&phy->sas_prim_lock, flags);

	SAS_DPRINTK("broadcast received: %d\n", prim);
	sas_discover_event(phy->port, DISCE_REVALIDATE_DOMAIN);
}