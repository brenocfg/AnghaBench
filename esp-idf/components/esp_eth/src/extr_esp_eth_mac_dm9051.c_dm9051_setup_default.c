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
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  emac_dm9051_t ;

/* Variables and functions */
 int ATCR_AUTO_TX ; 
 int /*<<< orphan*/  DM9051_ATCR ; 
 int /*<<< orphan*/  DM9051_BPTR ; 
 int /*<<< orphan*/  DM9051_FCR ; 
 int /*<<< orphan*/  DM9051_FCTR ; 
 int /*<<< orphan*/  DM9051_INTCKCR ; 
 int /*<<< orphan*/  DM9051_INTCR ; 
 int /*<<< orphan*/  DM9051_ISR ; 
 int /*<<< orphan*/  DM9051_MEMSCR ; 
 int /*<<< orphan*/  DM9051_MPTRCR ; 
 int /*<<< orphan*/  DM9051_NCR ; 
 int /*<<< orphan*/  DM9051_NSR ; 
 int /*<<< orphan*/  DM9051_RCR ; 
 int /*<<< orphan*/  DM9051_RCSCSR ; 
 int /*<<< orphan*/  DM9051_RLENCR ; 
 int /*<<< orphan*/  DM9051_TCR ; 
 int /*<<< orphan*/  DM9051_TCR2 ; 
 int /*<<< orphan*/  DM9051_TCSCR ; 
 int /*<<< orphan*/  DM9051_WCR ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int FCR_FLOW_ENABLE ; 
 int ISR_CLR_STATUS ; 
 int /*<<< orphan*/  MAC_CHECK (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MPTRCR_RST_RX ; 
 int MPTRCR_RST_TX ; 
 int NSR_TX1END ; 
 int NSR_TX2END ; 
 int NSR_WAKEST ; 
 int RCR_DIS_CRC ; 
 int RCR_DIS_LONG ; 
 int TCR2_RLCP ; 
 int TCSCR_IPCSE ; 
 int TCSCR_TCPCSE ; 
 int TCSCR_UDPCSE ; 
 scalar_t__ dm9051_register_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err ; 

__attribute__((used)) static esp_err_t dm9051_setup_default(emac_dm9051_t *emac)
{
    esp_err_t ret = ESP_OK;
    /* disable wakeup */
    MAC_CHECK(dm9051_register_write(emac, DM9051_NCR, 0x00) == ESP_OK, "write NCR failed", err, ESP_FAIL);
    MAC_CHECK(dm9051_register_write(emac, DM9051_WCR, 0x00) == ESP_OK, "write WCR failed", err, ESP_FAIL);
    /* stop transmitting, enable appending pad, crc for packets */
    MAC_CHECK(dm9051_register_write(emac, DM9051_TCR, 0x00) == ESP_OK, "write TCR failed", err, ESP_FAIL);
    /* stop receiving, no promiscuous mode, no runt packet(size < 64bytes), not all multicast packets*/
    /* discard long packet(size > 1522bytes) and crc error packet, enable watchdog */
    MAC_CHECK(dm9051_register_write(emac, DM9051_RCR, RCR_DIS_LONG | RCR_DIS_CRC) == ESP_OK, "write RCR failed", err, ESP_FAIL);
    /* send jam pattern (duration time = 1.15ms) when rx free space < 3k bytes */
    MAC_CHECK(dm9051_register_write(emac, DM9051_BPTR, 0x3F) == ESP_OK, "write BPTR failed", err, ESP_FAIL);
    /* flow control: high water threshold = 3k bytes, low water threshold = 8k bytes */
    MAC_CHECK(dm9051_register_write(emac, DM9051_FCTR, 0x38) == ESP_OK, "write FCTR failed", err, ESP_FAIL);
    /* enable flow control */
    MAC_CHECK(dm9051_register_write(emac, DM9051_FCR, FCR_FLOW_ENABLE) == ESP_OK, "write FCR failed", err, ESP_FAIL);
    /* retry late collision packet, at most two transmit command can be issued before transmit complete */
    MAC_CHECK(dm9051_register_write(emac, DM9051_TCR2, TCR2_RLCP) == ESP_OK, "write TCR2 failed", err, ESP_FAIL);
    /* enable auto transmit */
    MAC_CHECK(dm9051_register_write(emac, DM9051_ATCR, ATCR_AUTO_TX) == ESP_OK, "write ATCR failed", err, ESP_FAIL);
    /* generate checksum for UDP, TCP and IPv4 packets */
    MAC_CHECK(dm9051_register_write(emac, DM9051_TCSCR, TCSCR_IPCSE | TCSCR_TCPCSE | TCSCR_UDPCSE) == ESP_OK,
              "write TCSCR failed", err, ESP_FAIL);
    /* disable check sum for receive packets */
    MAC_CHECK(dm9051_register_write(emac, DM9051_RCSCSR, 0x00) == ESP_OK, "write RCSCSR failed", err, ESP_FAIL);
    /* interrupt pin config: push-pull output, active high */
    MAC_CHECK(dm9051_register_write(emac, DM9051_INTCR, 0x00) == ESP_OK, "write INTCR failed", err, ESP_FAIL);
    MAC_CHECK(dm9051_register_write(emac, DM9051_INTCKCR, 0x00) == ESP_OK, "write INTCKCR failed", err, ESP_FAIL);
    /* no length limitation for rx packets */
    MAC_CHECK(dm9051_register_write(emac, DM9051_RLENCR, 0x00) == ESP_OK, "write RLENCR failed", err, ESP_FAIL);
    /* 3K-byte for TX and 13K-byte for RX */
    MAC_CHECK(dm9051_register_write(emac, DM9051_MEMSCR, 0x00) == ESP_OK, "write MEMSCR failed", err, ESP_FAIL);
    /* reset tx and rx memory pointer */
    MAC_CHECK(dm9051_register_write(emac, DM9051_MPTRCR, MPTRCR_RST_RX | MPTRCR_RST_TX) == ESP_OK,
              "write MPTRCR failed", err, ESP_FAIL);
    /* clear network status: wakeup event, tx complete */
    MAC_CHECK(dm9051_register_write(emac, DM9051_NSR, NSR_WAKEST | NSR_TX2END | NSR_TX1END) == ESP_OK, "write NSR failed", err, ESP_FAIL);
    /* clear interrupt status */
    MAC_CHECK(dm9051_register_write(emac, DM9051_ISR, ISR_CLR_STATUS) == ESP_OK, "write ISR failed", err, ESP_FAIL);
    return ESP_OK;
err:
    return ret;
}