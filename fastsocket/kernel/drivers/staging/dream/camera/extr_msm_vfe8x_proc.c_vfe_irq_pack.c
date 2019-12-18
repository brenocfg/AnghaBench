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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_irqenable {int /*<<< orphan*/  violationIrq; int /*<<< orphan*/  axiErrorIrq; int /*<<< orphan*/  asyncTimer3Irq; int /*<<< orphan*/  asyncTimer2Irq; int /*<<< orphan*/  asyncTimer1Irq; int /*<<< orphan*/  asyncTimer0Irq; int /*<<< orphan*/  syncTimer2Irq; int /*<<< orphan*/  syncTimer1Irq; int /*<<< orphan*/  syncTimer0Irq; int /*<<< orphan*/  awbOverflowIrq; int /*<<< orphan*/  afOverflowIrq; int /*<<< orphan*/  busOverflowIrq; int /*<<< orphan*/  viewIrq; int /*<<< orphan*/  encIrq; int /*<<< orphan*/  histPingpongIrq; int /*<<< orphan*/  awbPingpongIrq; int /*<<< orphan*/  afPingpongIrq; int /*<<< orphan*/  rdPingpongIrq; int /*<<< orphan*/  viewCbcrPingpongIrq; int /*<<< orphan*/  viewYPingpongIrq; int /*<<< orphan*/  encCbcrPingpongIrq; int /*<<< orphan*/  encYPingpongIrq; int /*<<< orphan*/  resetAckIrq; int /*<<< orphan*/  regUpdateIrq; int /*<<< orphan*/  ceIrq; int /*<<< orphan*/  camifOverflowIrq; int /*<<< orphan*/  camifEpoch2Irq; int /*<<< orphan*/  camifEpoch1Irq; int /*<<< orphan*/  camifEofIrq; int /*<<< orphan*/  camifEolIrq; int /*<<< orphan*/  camifSofIrq; int /*<<< orphan*/  camifErrorIrq; } ;
struct vfe_interrupt_mask {int /*<<< orphan*/  violationIrq; int /*<<< orphan*/  axiErrorIrq; int /*<<< orphan*/  asyncTimer3Irq; int /*<<< orphan*/  asyncTimer2Irq; int /*<<< orphan*/  asyncTimer1Irq; int /*<<< orphan*/  asyncTimer0Irq; int /*<<< orphan*/  syncTimer2Irq; int /*<<< orphan*/  syncTimer1Irq; int /*<<< orphan*/  syncTimer0Irq; int /*<<< orphan*/  awbOverflowIrq; int /*<<< orphan*/  afOverflowIrq; int /*<<< orphan*/  busOverflowIrq; int /*<<< orphan*/  viewIrq; int /*<<< orphan*/  encIrq; int /*<<< orphan*/  histPingpongIrq; int /*<<< orphan*/  awbPingpongIrq; int /*<<< orphan*/  afPingpongIrq; int /*<<< orphan*/  rdPingpongIrq; int /*<<< orphan*/  viewCbcrPingpongIrq; int /*<<< orphan*/  viewYPingpongIrq; int /*<<< orphan*/  encCbcrPingpongIrq; int /*<<< orphan*/  encYPingpongIrq; int /*<<< orphan*/  resetAckIrq; int /*<<< orphan*/  regUpdateIrq; int /*<<< orphan*/  ceIrq; int /*<<< orphan*/  camifOverflowIrq; int /*<<< orphan*/  camifEpoch2Irq; int /*<<< orphan*/  camifEpoch1Irq; int /*<<< orphan*/  camifEofIrq; int /*<<< orphan*/  camifEolIrq; int /*<<< orphan*/  camifSofIrq; int /*<<< orphan*/  camifErrorIrq; } ;
typedef  int /*<<< orphan*/  packedData ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vfe_irqenable*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t vfe_irq_pack(struct vfe_interrupt_mask data)
{
	struct vfe_irqenable packedData;

	memset(&packedData, 0, sizeof(packedData));

	packedData.camifErrorIrq          = data.camifErrorIrq;
	packedData.camifSofIrq            = data.camifSofIrq;
	packedData.camifEolIrq            = data.camifEolIrq;
	packedData.camifEofIrq            = data.camifEofIrq;
	packedData.camifEpoch1Irq         = data.camifEpoch1Irq;
	packedData.camifEpoch2Irq         = data.camifEpoch2Irq;
	packedData.camifOverflowIrq       = data.camifOverflowIrq;
	packedData.ceIrq                  = data.ceIrq;
	packedData.regUpdateIrq           = data.regUpdateIrq;
	packedData.resetAckIrq            = data.resetAckIrq;
	packedData.encYPingpongIrq        = data.encYPingpongIrq;
	packedData.encCbcrPingpongIrq     = data.encCbcrPingpongIrq;
	packedData.viewYPingpongIrq       = data.viewYPingpongIrq;
	packedData.viewCbcrPingpongIrq    = data.viewCbcrPingpongIrq;
	packedData.rdPingpongIrq          = data.rdPingpongIrq;
	packedData.afPingpongIrq          = data.afPingpongIrq;
	packedData.awbPingpongIrq         = data.awbPingpongIrq;
	packedData.histPingpongIrq        = data.histPingpongIrq;
	packedData.encIrq                 = data.encIrq;
	packedData.viewIrq                = data.viewIrq;
	packedData.busOverflowIrq         = data.busOverflowIrq;
	packedData.afOverflowIrq          = data.afOverflowIrq;
	packedData.awbOverflowIrq         = data.awbOverflowIrq;
	packedData.syncTimer0Irq          = data.syncTimer0Irq;
	packedData.syncTimer1Irq          = data.syncTimer1Irq;
	packedData.syncTimer2Irq          = data.syncTimer2Irq;
	packedData.asyncTimer0Irq         = data.asyncTimer0Irq;
	packedData.asyncTimer1Irq         = data.asyncTimer1Irq;
	packedData.asyncTimer2Irq         = data.asyncTimer2Irq;
	packedData.asyncTimer3Irq         = data.asyncTimer3Irq;
	packedData.axiErrorIrq            = data.axiErrorIrq;
	packedData.violationIrq           = data.violationIrq;

	return *((uint32_t *)&packedData);
}