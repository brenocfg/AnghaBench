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
typedef  int u32 ;
struct cas {int cas_flags; int mac_rx_cfg; scalar_t__ regs; int /*<<< orphan*/ * stat_lock; scalar_t__ crc_size; TYPE_1__* dev; } ;
struct TYPE_2__ {unsigned char* dev_addr; } ;

/* Variables and functions */
 int CAS_BASE (int /*<<< orphan*/ ,int) ; 
 int CAS_FLAG_SATURN ; 
 int CAS_FLAG_TARGET_ABORT ; 
 int CAS_MAX_MTU ; 
 int CAWR_RR_DIS ; 
 int ETH_HLEN ; 
 int ETH_ZLEN ; 
 int INF_BURST_EN ; 
 int /*<<< orphan*/  MAC_FRAMESIZE_MAX_BURST ; 
 int /*<<< orphan*/  MAC_FRAMESIZE_MAX_FRAME ; 
 int MAC_RX_FRAME_RECV ; 
 int MAC_TX_FRAME_XMIT ; 
 size_t N_TX_RINGS ; 
 scalar_t__ REG_CAWR ; 
 scalar_t__ REG_INF_BURST ; 
 scalar_t__ REG_MAC_ADDRN (int) ; 
 scalar_t__ REG_MAC_ADDR_FILTER0 ; 
 scalar_t__ REG_MAC_ADDR_FILTER0_MASK ; 
 scalar_t__ REG_MAC_ADDR_FILTER1 ; 
 scalar_t__ REG_MAC_ADDR_FILTER2 ; 
 scalar_t__ REG_MAC_ADDR_FILTER2_1_MASK ; 
 scalar_t__ REG_MAC_ATTEMPT_LIMIT ; 
 scalar_t__ REG_MAC_CTRL_MASK ; 
 scalar_t__ REG_MAC_CTRL_TYPE ; 
 scalar_t__ REG_MAC_FRAMESIZE_MAX ; 
 scalar_t__ REG_MAC_FRAMESIZE_MIN ; 
 scalar_t__ REG_MAC_IPG0 ; 
 scalar_t__ REG_MAC_IPG1 ; 
 scalar_t__ REG_MAC_IPG2 ; 
 scalar_t__ REG_MAC_JAM_SIZE ; 
 scalar_t__ REG_MAC_PA_SIZE ; 
 scalar_t__ REG_MAC_RANDOM_SEED ; 
 scalar_t__ REG_MAC_RX_CFG ; 
 scalar_t__ REG_MAC_RX_MASK ; 
 scalar_t__ REG_MAC_SEND_PAUSE ; 
 scalar_t__ REG_MAC_SLOT_TIME ; 
 scalar_t__ REG_MAC_TX_MASK ; 
 int /*<<< orphan*/  cas_clear_mac_err (struct cas*) ; 
 int /*<<< orphan*/  cas_mac_reset (struct cas*) ; 
 void* cas_setup_multicast (struct cas*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_init_mac(struct cas *cp)
{
	unsigned char *e = &cp->dev->dev_addr[0];
	int i;
#ifdef CONFIG_CASSINI_MULTICAST_REG_WRITE
	u32 rxcfg;
#endif
	cas_mac_reset(cp);

	/* setup core arbitration weight register */
	writel(CAWR_RR_DIS, cp->regs + REG_CAWR);

	/* XXX Use pci_dma_burst_advice() */
#if !defined(CONFIG_SPARC64) && !defined(CONFIG_ALPHA)
	/* set the infinite burst register for chips that don't have
	 * pci issues.
	 */
	if ((cp->cas_flags & CAS_FLAG_TARGET_ABORT) == 0)
		writel(INF_BURST_EN, cp->regs + REG_INF_BURST);
#endif

	writel(0x1BF0, cp->regs + REG_MAC_SEND_PAUSE);

	writel(0x00, cp->regs + REG_MAC_IPG0);
	writel(0x08, cp->regs + REG_MAC_IPG1);
	writel(0x04, cp->regs + REG_MAC_IPG2);

	/* change later for 802.3z */
	writel(0x40, cp->regs + REG_MAC_SLOT_TIME);

	/* min frame + FCS */
	writel(ETH_ZLEN + 4, cp->regs + REG_MAC_FRAMESIZE_MIN);

	/* Ethernet payload + header + FCS + optional VLAN tag. NOTE: we
	 * specify the maximum frame size to prevent RX tag errors on
	 * oversized frames.
	 */
	writel(CAS_BASE(MAC_FRAMESIZE_MAX_BURST, 0x2000) |
	       CAS_BASE(MAC_FRAMESIZE_MAX_FRAME,
			(CAS_MAX_MTU + ETH_HLEN + 4 + 4)),
	       cp->regs + REG_MAC_FRAMESIZE_MAX);

	/* NOTE: crc_size is used as a surrogate for half-duplex.
	 * workaround saturn half-duplex issue by increasing preamble
	 * size to 65 bytes.
	 */
	if ((cp->cas_flags & CAS_FLAG_SATURN) && cp->crc_size)
		writel(0x41, cp->regs + REG_MAC_PA_SIZE);
	else
		writel(0x07, cp->regs + REG_MAC_PA_SIZE);
	writel(0x04, cp->regs + REG_MAC_JAM_SIZE);
	writel(0x10, cp->regs + REG_MAC_ATTEMPT_LIMIT);
	writel(0x8808, cp->regs + REG_MAC_CTRL_TYPE);

	writel((e[5] | (e[4] << 8)) & 0x3ff, cp->regs + REG_MAC_RANDOM_SEED);

	writel(0, cp->regs + REG_MAC_ADDR_FILTER0);
	writel(0, cp->regs + REG_MAC_ADDR_FILTER1);
	writel(0, cp->regs + REG_MAC_ADDR_FILTER2);
	writel(0, cp->regs + REG_MAC_ADDR_FILTER2_1_MASK);
	writel(0, cp->regs + REG_MAC_ADDR_FILTER0_MASK);

	/* setup mac address in perfect filter array */
	for (i = 0; i < 45; i++)
		writel(0x0, cp->regs + REG_MAC_ADDRN(i));

	writel((e[4] << 8) | e[5], cp->regs + REG_MAC_ADDRN(0));
	writel((e[2] << 8) | e[3], cp->regs + REG_MAC_ADDRN(1));
	writel((e[0] << 8) | e[1], cp->regs + REG_MAC_ADDRN(2));

	writel(0x0001, cp->regs + REG_MAC_ADDRN(42));
	writel(0xc200, cp->regs + REG_MAC_ADDRN(43));
	writel(0x0180, cp->regs + REG_MAC_ADDRN(44));

#ifndef CONFIG_CASSINI_MULTICAST_REG_WRITE
	cp->mac_rx_cfg = cas_setup_multicast(cp);
#else
	/* WTZ: Do what Adrian did in cas_set_multicast. Doing
	 * a writel does not seem to be necessary because Cassini
	 * seems to preserve the configuration when we do the reset.
	 * If the chip is in trouble, though, it is not clear if we
	 * can really count on this behavior. cas_set_multicast uses
	 * spin_lock_irqsave, but we are called only in cas_init_hw and
	 * cas_init_hw is protected by cas_lock_all, which calls
	 * spin_lock_irq (so it doesn't need to save the flags, and
	 * we should be OK for the writel, as that is the only
	 * difference).
	 */
	cp->mac_rx_cfg = rxcfg = cas_setup_multicast(cp);
	writel(rxcfg, cp->regs + REG_MAC_RX_CFG);
#endif
	spin_lock(&cp->stat_lock[N_TX_RINGS]);
	cas_clear_mac_err(cp);
	spin_unlock(&cp->stat_lock[N_TX_RINGS]);

	/* Setup MAC interrupts.  We want to get all of the interesting
	 * counter expiration events, but we do not want to hear about
	 * normal rx/tx as the DMA engine tells us that.
	 */
	writel(MAC_TX_FRAME_XMIT, cp->regs + REG_MAC_TX_MASK);
	writel(MAC_RX_FRAME_RECV, cp->regs + REG_MAC_RX_MASK);

	/* Don't enable even the PAUSE interrupts for now, we
	 * make no use of those events other than to record them.
	 */
	writel(0xffffffff, cp->regs + REG_MAC_CTRL_MASK);
}