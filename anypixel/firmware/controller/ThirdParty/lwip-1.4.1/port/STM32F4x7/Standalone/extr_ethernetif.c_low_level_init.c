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
struct netif {int mtu; int flags; int /*<<< orphan*/ * hwaddr; int /*<<< orphan*/  hwaddr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMARxDscrTab ; 
 int /*<<< orphan*/ * DMATxDscrTab ; 
 int /*<<< orphan*/  ETHARP_HWADDR_LEN ; 
 int /*<<< orphan*/  ETH_DMARxDescChainInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_DMATxDescChainInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ETH_DMATxDescChecksumInsertionConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_DMATxDesc_ChecksumTCPUDPICMPFull ; 
 int /*<<< orphan*/  ETH_MACAddressConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETH_MAC_Address0 ; 
 int /*<<< orphan*/  ETH_RXBUFNB ; 
 int /*<<< orphan*/  ETH_Start () ; 
 int ETH_TXBUFNB ; 
 int /*<<< orphan*/  MAC_ADDR0 ; 
 int /*<<< orphan*/  MAC_ADDR1 ; 
 int /*<<< orphan*/  MAC_ADDR2 ; 
 int /*<<< orphan*/  MAC_ADDR3 ; 
 int /*<<< orphan*/  MAC_ADDR4 ; 
 int NETIF_FLAG_BROADCAST ; 
 int NETIF_FLAG_ETHARP ; 
 int /*<<< orphan*/ ** Rx_Buff ; 
 int /*<<< orphan*/ ** Tx_Buff ; 
 int /*<<< orphan*/  mac_last_octet ; 

__attribute__((used)) static void low_level_init(struct netif *netif)
{
#ifdef CHECKSUM_BY_HARDWARE
  int i;
#endif
  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] =  MAC_ADDR0;
  netif->hwaddr[1] =  MAC_ADDR1;
  netif->hwaddr[2] =  MAC_ADDR2;
  netif->hwaddr[3] =  MAC_ADDR3;
  netif->hwaddr[4] =  MAC_ADDR4;
  netif->hwaddr[5] =  mac_last_octet;

  /* initialize MAC address in ethernet MAC */
  ETH_MACAddressConfig(ETH_MAC_Address0, netif->hwaddr);

  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

  /* Initialize Tx Descriptors list: Chain Mode */
  ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
  /* Initialize Rx Descriptors list: Chain Mode  */
  ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

#ifdef CHECKSUM_BY_HARDWARE
  /* Enable the TCP, UDP and ICMP checksum insertion for the Tx frames */
  for(i=0; i<ETH_TXBUFNB; i++)
    {
      ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
    }
#endif

   /* Note: TCP, UDP, ICMP checksum checking for received frame are enabled in DMA config */

  /* Enable MAC and DMA transmission and reception */
  ETH_Start();

}