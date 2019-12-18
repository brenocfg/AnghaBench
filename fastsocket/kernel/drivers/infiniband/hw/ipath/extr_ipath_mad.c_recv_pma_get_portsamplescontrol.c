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
typedef  int u8 ;
struct ipath_ibdev {int /*<<< orphan*/  pending_lock; int /*<<< orphan*/ * pma_counter_select; int /*<<< orphan*/  pma_tag; int /*<<< orphan*/  pma_sample_interval; int /*<<< orphan*/  pma_sample_start; int /*<<< orphan*/  pma_sample_status; TYPE_2__* dd; } ;
struct ipath_cregs {scalar_t__ cr_psstat; } ;
struct ib_smp {int dummy; } ;
struct ib_pma_portsamplescontrol {int port_select; int tick; int counter_width; int /*<<< orphan*/ * counter_select; int /*<<< orphan*/  tag; void* sample_interval; void* sample_start; int /*<<< orphan*/  sample_status; int /*<<< orphan*/  counter_mask0_9; } ;
struct TYPE_3__ {scalar_t__ attr_mod; int /*<<< orphan*/  status; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int ipath_link_speed_active; struct ipath_cregs* ipath_cregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_MASK0_9 ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_read_creg32 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int recv_pma_get_portsamplescontrol(struct ib_pma_mad *pmp,
					   struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portsamplescontrol *p =
		(struct ib_pma_portsamplescontrol *)pmp->data;
	struct ipath_ibdev *dev = to_idev(ibdev);
	struct ipath_cregs const *crp = dev->dd->ipath_cregs;
	unsigned long flags;
	u8 port_select = p->port_select;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->port_select = port_select;
	if (pmp->mad_hdr.attr_mod != 0 ||
	    (port_select != port && port_select != 0xFF))
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
	/*
	 * Ticks are 10x the link transfer period which for 2.5Gbs is 4
	 * nsec.  0 == 4 nsec., 1 == 8 nsec., ..., 255 == 1020 nsec.  Sample
	 * intervals are counted in ticks.  Since we use Linux timers, that
	 * count in jiffies, we can't sample for less than 1000 ticks if HZ
	 * == 1000 (4000 ticks if HZ is 250).  link_speed_active returns 2 for
	 * DDR, 1 for SDR, set the tick to 1 for DDR, 0 for SDR on chips that
	 * have hardware support for delaying packets.
	 */
	if (crp->cr_psstat)
		p->tick = dev->dd->ipath_link_speed_active - 1;
	else
		p->tick = 250;		/* 1 usec. */
	p->counter_width = 4;	/* 32 bit counters */
	p->counter_mask0_9 = COUNTER_MASK0_9;
	spin_lock_irqsave(&dev->pending_lock, flags);
	if (crp->cr_psstat)
		p->sample_status = ipath_read_creg32(dev->dd, crp->cr_psstat);
	else
		p->sample_status = dev->pma_sample_status;
	p->sample_start = cpu_to_be32(dev->pma_sample_start);
	p->sample_interval = cpu_to_be32(dev->pma_sample_interval);
	p->tag = cpu_to_be16(dev->pma_tag);
	p->counter_select[0] = dev->pma_counter_select[0];
	p->counter_select[1] = dev->pma_counter_select[1];
	p->counter_select[2] = dev->pma_counter_select[2];
	p->counter_select[3] = dev->pma_counter_select[3];
	p->counter_select[4] = dev->pma_counter_select[4];
	spin_unlock_irqrestore(&dev->pending_lock, flags);

	return reply((struct ib_smp *) pmp);
}