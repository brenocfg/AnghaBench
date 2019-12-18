#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct flexcop_pci {int count; int active_dma1_addr; int last_dma1_cur_pos; int /*<<< orphan*/  irq_lock; TYPE_3__* dma; struct flexcop_device* fc_dev; scalar_t__ last_irq; } ;
struct flexcop_device {TYPE_4__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {int dma_cur_addr; } ;
struct TYPE_7__ {int DMA1_IRQ_Status; int DMA1_Timer_Status; scalar_t__ Transport_Error; scalar_t__ LLC_SNAP_FLAG_set; scalar_t__ Continuity_error_flag; scalar_t__ Data_receiver_error; } ;
struct TYPE_10__ {int raw; TYPE_2__ dma_0x8; TYPE_1__ irq_20c; } ;
typedef  TYPE_4__ flexcop_ibi_value ;
typedef  int dma_addr_t ;
struct TYPE_9__ {int size; int dma_addr0; scalar_t__ cpu_addr0; scalar_t__ cpu_addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  deb_chk (char*,...) ; 
 int /*<<< orphan*/  deb_irq (char*,...) ; 
 int /*<<< orphan*/  dma1_008 ; 
 int /*<<< orphan*/  flexcop_pass_dmx_data (struct flexcop_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  flexcop_pass_dmx_packets (struct flexcop_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  irq_20c ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_usecs (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_4__ stub1 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 TYPE_4__ stub2 (struct flexcop_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t flexcop_pci_isr(int irq, void *dev_id)
{
	struct flexcop_pci *fc_pci = dev_id;
	struct flexcop_device *fc = fc_pci->fc_dev;
	unsigned long flags;
	flexcop_ibi_value v;
	irqreturn_t ret = IRQ_HANDLED;

	spin_lock_irqsave(&fc_pci->irq_lock, flags);
	v = fc->read_ibi_reg(fc, irq_20c);

	/* errors */
	if (v.irq_20c.Data_receiver_error)
		deb_chk("data receiver error\n");
	if (v.irq_20c.Continuity_error_flag)
		deb_chk("Contunuity error flag is set\n");
	if (v.irq_20c.LLC_SNAP_FLAG_set)
		deb_chk("LLC_SNAP_FLAG_set is set\n");
	if (v.irq_20c.Transport_Error)
		deb_chk("Transport error\n");

	if ((fc_pci->count % 1000) == 0)
		deb_chk("%d valid irq took place so far\n", fc_pci->count);

	if (v.irq_20c.DMA1_IRQ_Status == 1) {
		if (fc_pci->active_dma1_addr == 0)
			flexcop_pass_dmx_packets(fc_pci->fc_dev,
					fc_pci->dma[0].cpu_addr0,
					fc_pci->dma[0].size / 188);
		else
			flexcop_pass_dmx_packets(fc_pci->fc_dev,
					fc_pci->dma[0].cpu_addr1,
					fc_pci->dma[0].size / 188);

		deb_irq("page change to page: %d\n",!fc_pci->active_dma1_addr);
		fc_pci->active_dma1_addr = !fc_pci->active_dma1_addr;
		/* for the timer IRQ we only can use buffer dmx feeding, because we don't have
		 * complete TS packets when reading from the DMA memory */
	} else if (v.irq_20c.DMA1_Timer_Status == 1) {
		dma_addr_t cur_addr =
			fc->read_ibi_reg(fc,dma1_008).dma_0x8.dma_cur_addr << 2;
		u32 cur_pos = cur_addr - fc_pci->dma[0].dma_addr0;

		deb_irq("%u irq: %08x cur_addr: %llx: cur_pos: %08x, "
			"last_cur_pos: %08x ",
				jiffies_to_usecs(jiffies - fc_pci->last_irq),
				v.raw, (unsigned long long)cur_addr, cur_pos,
				fc_pci->last_dma1_cur_pos);
		fc_pci->last_irq = jiffies;

		/* buffer end was reached, restarted from the beginning
		 * pass the data from last_cur_pos to the buffer end to the demux
		 */
		if (cur_pos < fc_pci->last_dma1_cur_pos) {
			deb_irq(" end was reached: passing %d bytes ",
				(fc_pci->dma[0].size*2 - 1) -
				fc_pci->last_dma1_cur_pos);
			flexcop_pass_dmx_data(fc_pci->fc_dev,
				fc_pci->dma[0].cpu_addr0 +
					fc_pci->last_dma1_cur_pos,
				(fc_pci->dma[0].size*2) -
					fc_pci->last_dma1_cur_pos);
			fc_pci->last_dma1_cur_pos = 0;
		}

		if (cur_pos > fc_pci->last_dma1_cur_pos) {
			deb_irq(" passing %d bytes ",
				cur_pos - fc_pci->last_dma1_cur_pos);
			flexcop_pass_dmx_data(fc_pci->fc_dev,
				fc_pci->dma[0].cpu_addr0 +
					fc_pci->last_dma1_cur_pos,
				cur_pos - fc_pci->last_dma1_cur_pos);
		}
		deb_irq("\n");

		fc_pci->last_dma1_cur_pos = cur_pos;
		fc_pci->count++;
	} else {
		deb_irq("isr for flexcop called, "
			"apparently without reason (%08x)\n", v.raw);
		ret = IRQ_NONE;
	}

	spin_unlock_irqrestore(&fc_pci->irq_lock, flags);
	return ret;
}