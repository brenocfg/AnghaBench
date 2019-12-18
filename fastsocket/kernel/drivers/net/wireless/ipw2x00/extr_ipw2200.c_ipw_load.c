#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct ipw_priv {int eeprom_delay; TYPE_2__* rxq; int /*<<< orphan*/  status; TYPE_1__* ieee; } ;
struct ipw_fw {char* data; int /*<<< orphan*/  fw_size; int /*<<< orphan*/  ucode_size; int /*<<< orphan*/  boot_size; } ;
struct firmware {scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  read; } ;
struct TYPE_5__ {int iw_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int) ; 
 int /*<<< orphan*/  IPW_EEPROM_LOAD_DISABLE ; 
 int /*<<< orphan*/  IPW_ERROR (char*,...) ; 
 int /*<<< orphan*/  IPW_INTA_BIT_FW_INITIALIZATION_DONE ; 
 int IPW_INTA_BIT_PARITY_ERROR ; 
 int /*<<< orphan*/  IPW_INTA_MASK_ALL ; 
 int /*<<< orphan*/  IPW_INTA_MASK_R ; 
 int /*<<< orphan*/  IPW_INTA_RW ; 
 scalar_t__ IPW_NIC_SRAM_LOWER_BOUND ; 
 scalar_t__ IPW_NIC_SRAM_UPPER_BOUND ; 
 int /*<<< orphan*/  IPW_RX_READ_INDEX ; 
 int /*<<< orphan*/  IPW_WARNING (char*) ; 
#define  IW_MODE_ADHOC 130 
#define  IW_MODE_INFRA 129 
#define  IW_MODE_MONITOR 128 
 int /*<<< orphan*/  STATUS_INT_ENABLED ; 
 int fw_loaded ; 
 int /*<<< orphan*/  ipw_eeprom_init_sram (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_enable_interrupts (struct ipw_priv*) ; 
 int ipw_get_fw (struct ipw_priv*,struct firmware const**,char*) ; 
 int ipw_load_firmware (struct ipw_priv*,char*,size_t) ; 
 int ipw_load_ucode (struct ipw_priv*,char*,size_t) ; 
 int ipw_poll_bit (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ipw_queue_reset (struct ipw_priv*) ; 
 int ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int ipw_reset_nic (struct ipw_priv*) ; 
 TYPE_2__* ipw_rx_queue_alloc (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_rx_queue_free (struct ipw_priv*,TYPE_2__*) ; 
 int /*<<< orphan*/  ipw_rx_queue_replenish (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_rx_queue_reset (struct ipw_priv*,TYPE_2__*) ; 
 int /*<<< orphan*/  ipw_start_nic (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_stop_nic (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_tx_queue_free (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_zero_memory (struct ipw_priv*,scalar_t__,scalar_t__) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static int ipw_load(struct ipw_priv *priv)
{
#ifndef CONFIG_PM
	const struct firmware *raw = NULL;
#endif
	struct ipw_fw *fw;
	u8 *boot_img, *ucode_img, *fw_img;
	u8 *name = NULL;
	int rc = 0, retries = 3;

	switch (priv->ieee->iw_mode) {
	case IW_MODE_ADHOC:
		name = "ipw2200-ibss.fw";
		break;
#ifdef CONFIG_IPW2200_MONITOR
	case IW_MODE_MONITOR:
		name = "ipw2200-sniffer.fw";
		break;
#endif
	case IW_MODE_INFRA:
		name = "ipw2200-bss.fw";
		break;
	}

	if (!name) {
		rc = -EINVAL;
		goto error;
	}

#ifdef CONFIG_PM
	if (!fw_loaded) {
#endif
		rc = ipw_get_fw(priv, &raw, name);
		if (rc < 0)
			goto error;
#ifdef CONFIG_PM
	}
#endif

	fw = (void *)raw->data;
	boot_img = &fw->data[0];
	ucode_img = &fw->data[le32_to_cpu(fw->boot_size)];
	fw_img = &fw->data[le32_to_cpu(fw->boot_size) +
			   le32_to_cpu(fw->ucode_size)];

	if (rc < 0)
		goto error;

	if (!priv->rxq)
		priv->rxq = ipw_rx_queue_alloc(priv);
	else
		ipw_rx_queue_reset(priv, priv->rxq);
	if (!priv->rxq) {
		IPW_ERROR("Unable to initialize Rx queue\n");
		goto error;
	}

      retry:
	/* Ensure interrupts are disabled */
	ipw_write32(priv, IPW_INTA_MASK_R, ~IPW_INTA_MASK_ALL);
	priv->status &= ~STATUS_INT_ENABLED;

	/* ack pending interrupts */
	ipw_write32(priv, IPW_INTA_RW, IPW_INTA_MASK_ALL);

	ipw_stop_nic(priv);

	rc = ipw_reset_nic(priv);
	if (rc < 0) {
		IPW_ERROR("Unable to reset NIC\n");
		goto error;
	}

	ipw_zero_memory(priv, IPW_NIC_SRAM_LOWER_BOUND,
			IPW_NIC_SRAM_UPPER_BOUND - IPW_NIC_SRAM_LOWER_BOUND);

	/* DMA the initial boot firmware into the device */
	rc = ipw_load_firmware(priv, boot_img, le32_to_cpu(fw->boot_size));
	if (rc < 0) {
		IPW_ERROR("Unable to load boot firmware: %d\n", rc);
		goto error;
	}

	/* kick start the device */
	ipw_start_nic(priv);

	/* wait for the device to finish its initial startup sequence */
	rc = ipw_poll_bit(priv, IPW_INTA_RW,
			  IPW_INTA_BIT_FW_INITIALIZATION_DONE, 500);
	if (rc < 0) {
		IPW_ERROR("device failed to boot initial fw image\n");
		goto error;
	}
	IPW_DEBUG_INFO("initial device response after %dms\n", rc);

	/* ack fw init done interrupt */
	ipw_write32(priv, IPW_INTA_RW, IPW_INTA_BIT_FW_INITIALIZATION_DONE);

	/* DMA the ucode into the device */
	rc = ipw_load_ucode(priv, ucode_img, le32_to_cpu(fw->ucode_size));
	if (rc < 0) {
		IPW_ERROR("Unable to load ucode: %d\n", rc);
		goto error;
	}

	/* stop nic */
	ipw_stop_nic(priv);

	/* DMA bss firmware into the device */
	rc = ipw_load_firmware(priv, fw_img, le32_to_cpu(fw->fw_size));
	if (rc < 0) {
		IPW_ERROR("Unable to load firmware: %d\n", rc);
		goto error;
	}
#ifdef CONFIG_PM
	fw_loaded = 1;
#endif

	ipw_write32(priv, IPW_EEPROM_LOAD_DISABLE, 0);

	rc = ipw_queue_reset(priv);
	if (rc < 0) {
		IPW_ERROR("Unable to initialize queues\n");
		goto error;
	}

	/* Ensure interrupts are disabled */
	ipw_write32(priv, IPW_INTA_MASK_R, ~IPW_INTA_MASK_ALL);
	/* ack pending interrupts */
	ipw_write32(priv, IPW_INTA_RW, IPW_INTA_MASK_ALL);

	/* kick start the device */
	ipw_start_nic(priv);

	if (ipw_read32(priv, IPW_INTA_RW) & IPW_INTA_BIT_PARITY_ERROR) {
		if (retries > 0) {
			IPW_WARNING("Parity error.  Retrying init.\n");
			retries--;
			goto retry;
		}

		IPW_ERROR("TODO: Handle parity error -- schedule restart?\n");
		rc = -EIO;
		goto error;
	}

	/* wait for the device */
	rc = ipw_poll_bit(priv, IPW_INTA_RW,
			  IPW_INTA_BIT_FW_INITIALIZATION_DONE, 500);
	if (rc < 0) {
		IPW_ERROR("device failed to start within 500ms\n");
		goto error;
	}
	IPW_DEBUG_INFO("device response after %dms\n", rc);

	/* ack fw init done interrupt */
	ipw_write32(priv, IPW_INTA_RW, IPW_INTA_BIT_FW_INITIALIZATION_DONE);

	/* read eeprom data and initialize the eeprom region of sram */
	priv->eeprom_delay = 1;
	ipw_eeprom_init_sram(priv);

	/* enable interrupts */
	ipw_enable_interrupts(priv);

	/* Ensure our queue has valid packets */
	ipw_rx_queue_replenish(priv);

	ipw_write32(priv, IPW_RX_READ_INDEX, priv->rxq->read);

	/* ack pending interrupts */
	ipw_write32(priv, IPW_INTA_RW, IPW_INTA_MASK_ALL);

#ifndef CONFIG_PM
	release_firmware(raw);
#endif
	return 0;

      error:
	if (priv->rxq) {
		ipw_rx_queue_free(priv, priv->rxq);
		priv->rxq = NULL;
	}
	ipw_tx_queue_free(priv);
	release_firmware(raw);
#ifdef CONFIG_PM
	fw_loaded = 0;
	raw = NULL;
#endif

	return rc;
}