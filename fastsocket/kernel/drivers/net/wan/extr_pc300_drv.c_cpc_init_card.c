#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int mem_start; int mem_end; int /*<<< orphan*/  name; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  mtu; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  irq; } ;
struct TYPE_18__ {struct net_device* dev; scalar_t__ line_off; scalar_t__ line_on; scalar_t__ trace_on; TYPE_6__* chan; } ;
typedef  TYPE_5__ pc300dev_t ;
struct TYPE_15__ {int /*<<< orphan*/  parity; int /*<<< orphan*/  encoding; } ;
struct TYPE_14__ {int /*<<< orphan*/  clock_type; scalar_t__ clock_rate; } ;
struct TYPE_16__ {int tslot_bitmap; int /*<<< orphan*/  proto; int /*<<< orphan*/  media; int /*<<< orphan*/  rx_sens; int /*<<< orphan*/  lbo; int /*<<< orphan*/  fr_mode; int /*<<< orphan*/  lcode; TYPE_2__ proto_settings; TYPE_1__ phys_settings; } ;
struct TYPE_19__ {int channel; int /*<<< orphan*/  nfree_tx_bd; scalar_t__ rx_last_bd; scalar_t__ rx_first_bd; scalar_t__ tx_next_bd; scalar_t__ tx_first_bd; TYPE_3__ conf; TYPE_7__* card; TYPE_5__ d; } ;
typedef  TYPE_6__ pc300ch_t ;
struct TYPE_17__ {int ramsize; int type; int cpld_id; int nchan; int ramphys; int /*<<< orphan*/  irq; int /*<<< orphan*/  bus; scalar_t__ cpld_reg1; scalar_t__ falcbase; int /*<<< orphan*/  cpld_reg2; scalar_t__ scabase; int /*<<< orphan*/  clock; scalar_t__ gpioc_reg; scalar_t__ plxbase; scalar_t__ intctl_reg; } ;
struct TYPE_20__ {int /*<<< orphan*/  card_lock; TYPE_4__ hw; TYPE_6__* chan; } ;
typedef  TYPE_7__ pc300_t ;
struct TYPE_21__ {int /*<<< orphan*/  attach; int /*<<< orphan*/  xmit; } ;
typedef  TYPE_8__ hdlc_device ;

/* Variables and functions */
 scalar_t__ BTCR ; 
 int /*<<< orphan*/  CLOCK_EXT ; 
 scalar_t__ CPLD_ID_REG ; 
 scalar_t__ CPLD_REG1 ; 
 int CPLD_REG1_GLOBAL_CLK ; 
 int /*<<< orphan*/  CPLD_REG2 ; 
 scalar_t__ CPLD_V2_REG1 ; 
 int /*<<< orphan*/  CPLD_V2_REG2 ; 
 scalar_t__ DMER ; 
 int /*<<< orphan*/  ENCODING_NRZ ; 
 int /*<<< orphan*/  IF_IFACE_T1 ; 
 int /*<<< orphan*/  IF_IFACE_V35 ; 
 int /*<<< orphan*/  IF_IFACE_X21 ; 
 int /*<<< orphan*/  IF_PROTO_PPP ; 
 scalar_t__ N_DMA_RX_BUF ; 
 int /*<<< orphan*/  N_DMA_TX_BUF ; 
 int /*<<< orphan*/  PARITY_CRC16_PR1_CCITT ; 
 int /*<<< orphan*/  PC300_DEF_MTU ; 
 int /*<<< orphan*/  PC300_FR_ESF ; 
 int /*<<< orphan*/  PC300_LBO_0_DB ; 
 int /*<<< orphan*/  PC300_LC_B8ZS ; 
 int /*<<< orphan*/  PC300_OSC_CLOCK ; 
 int /*<<< orphan*/  PC300_PCI_CLOCK ; 
 int /*<<< orphan*/  PC300_PMC ; 
#define  PC300_RSV 130 
 int /*<<< orphan*/  PC300_RX_SENS_SH ; 
#define  PC300_TE 129 
 int /*<<< orphan*/  PC300_TX_QUEUE_LEN ; 
 int /*<<< orphan*/  PC300_TX_TIMEOUT ; 
#define  PC300_X21 128 
 scalar_t__ PCR ; 
 int PCR_PR2 ; 
 scalar_t__ WCRL ; 
 struct net_device* alloc_hdlcdev (TYPE_5__*) ; 
 int /*<<< orphan*/  cpc_attach ; 
 int /*<<< orphan*/  cpc_netdev_ops ; 
 int /*<<< orphan*/  cpc_queue_xmit ; 
 int cpc_readb (scalar_t__) ; 
 int cpc_readl (scalar_t__) ; 
 int cpc_readw (scalar_t__) ; 
 int /*<<< orphan*/  cpc_writeb (scalar_t__,int) ; 
 int /*<<< orphan*/  cpc_writel (scalar_t__,int) ; 
 int /*<<< orphan*/  cpc_writew (scalar_t__,int) ; 
 int detect_ram (TYPE_7__*) ; 
 TYPE_8__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  plx_init (TYPE_7__*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ register_hdlc_device (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpc_init_card(pc300_t * card)
{
	int i, devcount = 0;
	static int board_nbr = 1;

	/* Enable interrupts on the PCI bridge */
	plx_init(card);
	cpc_writew(card->hw.plxbase + card->hw.intctl_reg,
		   cpc_readw(card->hw.plxbase + card->hw.intctl_reg) | 0x0040);

#ifdef USE_PCI_CLOCK
	/* Set board clock to PCI clock */
	cpc_writel(card->hw.plxbase + card->hw.gpioc_reg,
		   cpc_readl(card->hw.plxbase + card->hw.gpioc_reg) | 0x00000004UL);
	card->hw.clock = PC300_PCI_CLOCK;
#else
	/* Set board clock to internal oscillator clock */
	cpc_writel(card->hw.plxbase + card->hw.gpioc_reg,
		   cpc_readl(card->hw.plxbase + card->hw.gpioc_reg) & ~0x00000004UL);
	card->hw.clock = PC300_OSC_CLOCK;
#endif

	/* Detect actual on-board RAM size */
	card->hw.ramsize = detect_ram(card);

	/* Set Global SCA-II registers */
	cpc_writeb(card->hw.scabase + PCR, PCR_PR2);
	cpc_writeb(card->hw.scabase + BTCR, 0x10);
	cpc_writeb(card->hw.scabase + WCRL, 0);
	cpc_writeb(card->hw.scabase + DMER, 0x80);

	if (card->hw.type == PC300_TE) {
		u8 reg1;

		/* Check CPLD version */
		reg1 = cpc_readb(card->hw.falcbase + CPLD_REG1);
		cpc_writeb(card->hw.falcbase + CPLD_REG1, (reg1 + 0x5a));
		if (cpc_readb(card->hw.falcbase + CPLD_REG1) == reg1) {
			/* New CPLD */
			card->hw.cpld_id = cpc_readb(card->hw.falcbase + CPLD_ID_REG);
			card->hw.cpld_reg1 = CPLD_V2_REG1;
			card->hw.cpld_reg2 = CPLD_V2_REG2;
		} else {
			/* old CPLD */
			card->hw.cpld_id = 0;
			card->hw.cpld_reg1 = CPLD_REG1;
			card->hw.cpld_reg2 = CPLD_REG2;
			cpc_writeb(card->hw.falcbase + CPLD_REG1, reg1);
		}

		/* Enable the board's global clock */
		cpc_writeb(card->hw.falcbase + card->hw.cpld_reg1,
			   cpc_readb(card->hw.falcbase + card->hw.cpld_reg1) |
			   CPLD_REG1_GLOBAL_CLK);

	}

	for (i = 0; i < card->hw.nchan; i++) {
		pc300ch_t *chan = &card->chan[i];
		pc300dev_t *d = &chan->d;
		hdlc_device *hdlc;
		struct net_device *dev;

		chan->card = card;
		chan->channel = i;
		chan->conf.phys_settings.clock_rate = 0;
		chan->conf.phys_settings.clock_type = CLOCK_EXT;
		chan->conf.proto_settings.encoding = ENCODING_NRZ;
		chan->conf.proto_settings.parity = PARITY_CRC16_PR1_CCITT;
		switch (card->hw.type) {
			case PC300_TE:
				chan->conf.media = IF_IFACE_T1;
				chan->conf.lcode = PC300_LC_B8ZS;
				chan->conf.fr_mode = PC300_FR_ESF;
				chan->conf.lbo = PC300_LBO_0_DB;
				chan->conf.rx_sens = PC300_RX_SENS_SH;
				chan->conf.tslot_bitmap = 0xffffffffUL;
				break;

			case PC300_X21:
				chan->conf.media = IF_IFACE_X21;
				break;

			case PC300_RSV:
			default:
				chan->conf.media = IF_IFACE_V35;
				break;
		}
		chan->conf.proto = IF_PROTO_PPP;
		chan->tx_first_bd = 0;
		chan->tx_next_bd = 0;
		chan->rx_first_bd = 0;
		chan->rx_last_bd = N_DMA_RX_BUF - 1;
		chan->nfree_tx_bd = N_DMA_TX_BUF;

		d->chan = chan;
		d->trace_on = 0;
		d->line_on = 0;
		d->line_off = 0;

		dev = alloc_hdlcdev(d);
		if (dev == NULL)
			continue;

		hdlc = dev_to_hdlc(dev);
		hdlc->xmit = cpc_queue_xmit;
		hdlc->attach = cpc_attach;
		d->dev = dev;
		dev->mem_start = card->hw.ramphys;
		dev->mem_end = card->hw.ramphys + card->hw.ramsize - 1;
		dev->irq = card->hw.irq;
		dev->tx_queue_len = PC300_TX_QUEUE_LEN;
		dev->mtu = PC300_DEF_MTU;

		dev->netdev_ops = &cpc_netdev_ops;
		dev->watchdog_timeo = PC300_TX_TIMEOUT;

		if (register_hdlc_device(dev) == 0) {
			printk("%s: Cyclades-PC300/", dev->name);
			switch (card->hw.type) {
				case PC300_TE:
					if (card->hw.bus == PC300_PMC) {
						printk("TE-M");
					} else {
						printk("TE  ");
					}
					break;

				case PC300_X21:
					printk("X21 ");
					break;

				case PC300_RSV:
				default:
					printk("RSV ");
					break;
			}
			printk (" #%d, %dKB of RAM at 0x%08x, IRQ%d, channel %d.\n",
				 board_nbr, card->hw.ramsize / 1024,
				 card->hw.ramphys, card->hw.irq, i + 1);
			devcount++;
		} else {
			printk ("Dev%d on card(0x%08x): unable to allocate i/f name.\n",
				 i + 1, card->hw.ramphys);
			free_netdev(dev);
			continue;
		}
	}
	spin_lock_init(&card->card_lock);

	board_nbr++;
}