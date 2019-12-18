#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  collisions; int /*<<< orphan*/  late_collisions; int /*<<< orphan*/  excessive_collisions; int /*<<< orphan*/  tx_deferred; int /*<<< orphan*/  first_collision; int /*<<< orphan*/  tx_uflo; int /*<<< orphan*/  max_pkt_error; int /*<<< orphan*/  norcvbuf; int /*<<< orphan*/  rx_ov_flow; int /*<<< orphan*/  crc_err; int /*<<< orphan*/  other_errors; int /*<<< orphan*/  length_err; int /*<<< orphan*/  alignment_err; int /*<<< orphan*/  code_violations; } ;
struct et131x_adapter {TYPE_7__ Stats; TYPE_4__* regs; } ;
struct TYPE_14__ {scalar_t__ rdrp; scalar_t__ rovr; scalar_t__ rcde; scalar_t__ rfrg; scalar_t__ rflr; scalar_t__ raln; scalar_t__ rfcs; } ;
struct TYPE_18__ {TYPE_5__ bits; void* value; } ;
struct TYPE_15__ {scalar_t__ tncl; scalar_t__ tlcl; scalar_t__ tmcl; scalar_t__ tdfr; scalar_t__ tscl; scalar_t__ tund; scalar_t__ tovr; } ;
struct TYPE_17__ {TYPE_6__ bits; void* value; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_12__ {TYPE_2__ Carry2; TYPE_1__ Carry1; } ;
struct TYPE_13__ {TYPE_3__ macStat; } ;
typedef  TYPE_8__ MAC_STAT_REG_2_t ;
typedef  TYPE_9__ MAC_STAT_REG_1_t ;

/* Variables and functions */
 scalar_t__ COUNTER_WRAP_12_BIT ; 
 scalar_t__ COUNTER_WRAP_16_BIT ; 
 void* readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (void*,int /*<<< orphan*/ *) ; 

void HandleMacStatInterrupt(struct et131x_adapter *etdev)
{
	MAC_STAT_REG_1_t Carry1;
	MAC_STAT_REG_2_t Carry2;

	/* Read the interrupt bits from the register(s).  These are Clear On
	 * Write.
	 */
	Carry1.value = readl(&etdev->regs->macStat.Carry1.value);
	Carry2.value = readl(&etdev->regs->macStat.Carry2.value);

	writel(Carry1.value, &etdev->regs->macStat.Carry1.value);
	writel(Carry2.value, &etdev->regs->macStat.Carry2.value);

	/* We need to do update the host copy of all the MAC_STAT counters.
	 * For each counter, check it's overflow bit.  If the overflow bit is
	 * set, then increment the host version of the count by one complete
	 * revolution of the counter.  This routine is called when the counter
	 * block indicates that one of the counters has wrapped.
	 */
	if (Carry1.bits.rfcs)
		etdev->Stats.code_violations += COUNTER_WRAP_16_BIT;
	if (Carry1.bits.raln)
		etdev->Stats.alignment_err += COUNTER_WRAP_12_BIT;
	if (Carry1.bits.rflr)
		etdev->Stats.length_err += COUNTER_WRAP_16_BIT;
	if (Carry1.bits.rfrg)
		etdev->Stats.other_errors += COUNTER_WRAP_16_BIT;
	if (Carry1.bits.rcde)
		etdev->Stats.crc_err += COUNTER_WRAP_16_BIT;
	if (Carry1.bits.rovr)
		etdev->Stats.rx_ov_flow += COUNTER_WRAP_16_BIT;
	if (Carry1.bits.rdrp)
		etdev->Stats.norcvbuf += COUNTER_WRAP_16_BIT;
	if (Carry2.bits.tovr)
		etdev->Stats.max_pkt_error += COUNTER_WRAP_12_BIT;
	if (Carry2.bits.tund)
		etdev->Stats.tx_uflo += COUNTER_WRAP_12_BIT;
	if (Carry2.bits.tscl)
		etdev->Stats.first_collision += COUNTER_WRAP_12_BIT;
	if (Carry2.bits.tdfr)
		etdev->Stats.tx_deferred += COUNTER_WRAP_12_BIT;
	if (Carry2.bits.tmcl)
		etdev->Stats.excessive_collisions += COUNTER_WRAP_12_BIT;
	if (Carry2.bits.tlcl)
		etdev->Stats.late_collisions += COUNTER_WRAP_12_BIT;
	if (Carry2.bits.tncl)
		etdev->Stats.collisions += COUNTER_WRAP_12_BIT;
}