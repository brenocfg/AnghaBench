#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ETH_HashTableHigh; int ETH_HashTableLow; int ETH_PauseTime; int ETH_VLANTagIdentifier; int ETH_DescriptorSkipLength; int /*<<< orphan*/  ETH_DMAArbitration; int /*<<< orphan*/  ETH_TxDMABurstLength; int /*<<< orphan*/  ETH_RxDMABurstLength; int /*<<< orphan*/  ETH_FixedBurst; int /*<<< orphan*/  ETH_AddressAlignedBeats; int /*<<< orphan*/  ETH_SecondFrameOperate; int /*<<< orphan*/  ETH_ReceiveThresholdControl; int /*<<< orphan*/  ETH_ForwardUndersizedGoodFrames; int /*<<< orphan*/  ETH_ForwardErrorFrames; int /*<<< orphan*/  ETH_TransmitThresholdControl; int /*<<< orphan*/  ETH_TransmitStoreForward; int /*<<< orphan*/  ETH_FlushReceivedFrame; int /*<<< orphan*/  ETH_ReceiveStoreForward; int /*<<< orphan*/  ETH_DropTCPIPChecksumErrorFrame; int /*<<< orphan*/  ETH_VLANTagComparison; int /*<<< orphan*/  ETH_TransmitFlowControl; int /*<<< orphan*/  ETH_ReceiveFlowControl; int /*<<< orphan*/  ETH_UnicastPauseFrameDetect; int /*<<< orphan*/  ETH_PauseLowThreshold; int /*<<< orphan*/  ETH_ZeroQuantaPause; int /*<<< orphan*/  ETH_UnicastFramesFilter; int /*<<< orphan*/  ETH_MulticastFramesFilter; int /*<<< orphan*/  ETH_PromiscuousMode; int /*<<< orphan*/  ETH_DestinationAddrFilter; int /*<<< orphan*/  ETH_BroadcastFramesReception; int /*<<< orphan*/  ETH_PassControlFrames; int /*<<< orphan*/  ETH_SourceAddrFilter; int /*<<< orphan*/  ETH_ReceiveAll; int /*<<< orphan*/  ETH_DeferralCheck; int /*<<< orphan*/  ETH_BackOffLimit; int /*<<< orphan*/  ETH_AutomaticPadCRCStrip; int /*<<< orphan*/  ETH_RetryTransmission; int /*<<< orphan*/  ETH_ChecksumOffload; int /*<<< orphan*/  ETH_Mode; int /*<<< orphan*/  ETH_LoopbackMode; int /*<<< orphan*/  ETH_ReceiveOwn; int /*<<< orphan*/  ETH_Speed; int /*<<< orphan*/  ETH_CarrierSense; int /*<<< orphan*/  ETH_InterFrameGap; int /*<<< orphan*/  ETH_Jabber; int /*<<< orphan*/  ETH_Watchdog; int /*<<< orphan*/  ETH_AutoNegotiation; } ;
typedef  TYPE_1__ ETH_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_AddressAlignedBeats_Enable ; 
 int /*<<< orphan*/  ETH_AutoNegotiation_Enable ; 
 int /*<<< orphan*/  ETH_AutomaticPadCRCStrip_Disable ; 
 int /*<<< orphan*/  ETH_BackOffLimit_10 ; 
 int /*<<< orphan*/  ETH_BroadcastFramesReception_Disable ; 
 int /*<<< orphan*/  ETH_CarrierSense_Enable ; 
 int /*<<< orphan*/  ETH_ChecksumOffload_Disable ; 
 int /*<<< orphan*/  ETH_DMAArbitration_RoundRobin_RxTx_1_1 ; 
 int /*<<< orphan*/  ETH_DeferralCheck_Disable ; 
 int /*<<< orphan*/  ETH_DestinationAddrFilter_Normal ; 
 int /*<<< orphan*/  ETH_DropTCPIPChecksumErrorFrame_Disable ; 
 int /*<<< orphan*/  ETH_FixedBurst_Enable ; 
 int /*<<< orphan*/  ETH_FlushReceivedFrame_Enable ; 
 int /*<<< orphan*/  ETH_ForwardErrorFrames_Disable ; 
 int /*<<< orphan*/  ETH_ForwardUndersizedGoodFrames_Disable ; 
 int /*<<< orphan*/  ETH_InterFrameGap_96Bit ; 
 int /*<<< orphan*/  ETH_Jabber_Enable ; 
 int /*<<< orphan*/  ETH_LoopbackMode_Disable ; 
 int /*<<< orphan*/  ETH_Mode_FullDuplex ; 
 int /*<<< orphan*/  ETH_MulticastFramesFilter_Perfect ; 
 int /*<<< orphan*/  ETH_PassControlFrames_BlockAll ; 
 int /*<<< orphan*/  ETH_PauseLowThreshold_Minus4 ; 
 int /*<<< orphan*/  ETH_PromiscuousMode_Disable ; 
 int /*<<< orphan*/  ETH_ReceiveAll_Disable ; 
 int /*<<< orphan*/  ETH_ReceiveFlowControl_Disable ; 
 int /*<<< orphan*/  ETH_ReceiveOwn_Enable ; 
 int /*<<< orphan*/  ETH_ReceiveStoreForward_Enable ; 
 int /*<<< orphan*/  ETH_ReceiveThresholdControl_64Bytes ; 
 int /*<<< orphan*/  ETH_RetryTransmission_Enable ; 
 int /*<<< orphan*/  ETH_RxDMABurstLength_32Beat ; 
 int /*<<< orphan*/  ETH_SecondFrameOperate_Disable ; 
 int /*<<< orphan*/  ETH_SourceAddrFilter_Disable ; 
 int /*<<< orphan*/  ETH_Speed_100M ; 
 int /*<<< orphan*/  ETH_TransmitFlowControl_Disable ; 
 int /*<<< orphan*/  ETH_TransmitStoreForward_Enable ; 
 int /*<<< orphan*/  ETH_TransmitThresholdControl_64Bytes ; 
 int /*<<< orphan*/  ETH_TxDMABurstLength_32Beat ; 
 int /*<<< orphan*/  ETH_UnicastFramesFilter_Perfect ; 
 int /*<<< orphan*/  ETH_UnicastPauseFrameDetect_Disable ; 
 int /*<<< orphan*/  ETH_VLANTagComparison_16Bit ; 
 int /*<<< orphan*/  ETH_Watchdog_Enable ; 
 int /*<<< orphan*/  ETH_ZeroQuantaPause_Disable ; 

void ETH_StructInit(ETH_InitTypeDef* ETH_InitStruct)
{
  /* ETH_InitStruct members default value */
  /*------------------------   MAC Configuration   ---------------------------*/

  /* PHY Auto-negotiation enabled */
  ETH_InitStruct->ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;
  /* MAC watchdog enabled: cuts off long frame */
  ETH_InitStruct->ETH_Watchdog = ETH_Watchdog_Enable;
  /* MAC Jabber enabled in Half-duplex mode */
  ETH_InitStruct->ETH_Jabber = ETH_Jabber_Enable;
  /* Ethernet interframe gap set to 96 bits */
  ETH_InitStruct->ETH_InterFrameGap = ETH_InterFrameGap_96Bit;
  /* Carrier Sense Enabled in Half-Duplex mode */
  ETH_InitStruct->ETH_CarrierSense = ETH_CarrierSense_Enable;
  /* PHY speed configured to 100Mbit/s */
  ETH_InitStruct->ETH_Speed = ETH_Speed_100M;
  /* Receive own Frames in Half-Duplex mode enabled */
  ETH_InitStruct->ETH_ReceiveOwn = ETH_ReceiveOwn_Enable;
  /* MAC MII loopback disabled */
  ETH_InitStruct->ETH_LoopbackMode = ETH_LoopbackMode_Disable;
  /* Full-Duplex mode selected */
  ETH_InitStruct->ETH_Mode = ETH_Mode_FullDuplex;
  /* IPv4 and TCP/UDP/ICMP frame Checksum Offload disabled */
  ETH_InitStruct->ETH_ChecksumOffload = ETH_ChecksumOffload_Disable;
  /* Retry Transmission enabled for half-duplex mode */
  ETH_InitStruct->ETH_RetryTransmission = ETH_RetryTransmission_Enable;
  /* Automatic PAD/CRC strip disabled*/
  ETH_InitStruct->ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;
  /* half-duplex mode retransmission Backoff time_limit = 10 slot times*/
  ETH_InitStruct->ETH_BackOffLimit = ETH_BackOffLimit_10;
  /* half-duplex mode Deferral check disabled */
  ETH_InitStruct->ETH_DeferralCheck = ETH_DeferralCheck_Disable;
  /* Receive all frames disabled */
  ETH_InitStruct->ETH_ReceiveAll = ETH_ReceiveAll_Disable;
  /* Source address filtering (on the optional MAC addresses) disabled */
  ETH_InitStruct->ETH_SourceAddrFilter = ETH_SourceAddrFilter_Disable;
  /* Do not forward control frames that do not pass the address filtering */
  ETH_InitStruct->ETH_PassControlFrames = ETH_PassControlFrames_BlockAll;
  /* Disable reception of Broadcast frames */
  ETH_InitStruct->ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Disable;
  /* Normal Destination address filtering (not reverse addressing) */
  ETH_InitStruct->ETH_DestinationAddrFilter = ETH_DestinationAddrFilter_Normal;
  /* Promiscuous address filtering mode disabled */
  ETH_InitStruct->ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;
  /* Perfect address filtering for multicast addresses */
  ETH_InitStruct->ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;
  /* Perfect address filtering for unicast addresses */
  ETH_InitStruct->ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;
  /* Initialize hash table high and low regs */
  ETH_InitStruct->ETH_HashTableHigh = 0x0;
  ETH_InitStruct->ETH_HashTableLow = 0x0;
  /* Flow control config (flow control disabled)*/
  ETH_InitStruct->ETH_PauseTime = 0x0;
  ETH_InitStruct->ETH_ZeroQuantaPause = ETH_ZeroQuantaPause_Disable;
  ETH_InitStruct->ETH_PauseLowThreshold = ETH_PauseLowThreshold_Minus4;
  ETH_InitStruct->ETH_UnicastPauseFrameDetect = ETH_UnicastPauseFrameDetect_Disable;
  ETH_InitStruct->ETH_ReceiveFlowControl = ETH_ReceiveFlowControl_Disable;
  ETH_InitStruct->ETH_TransmitFlowControl = ETH_TransmitFlowControl_Disable;
  /* VLANtag config (VLAN field not checked) */
  ETH_InitStruct->ETH_VLANTagComparison = ETH_VLANTagComparison_16Bit;
  ETH_InitStruct->ETH_VLANTagIdentifier = 0x0;

  /*---------------------- DMA Configuration   -------------------------------*/

  /* Drops frames with with TCP/IP checksum errors */
  ETH_InitStruct->ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Disable;
  /* Store and forward mode enabled for receive */
  ETH_InitStruct->ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;
  /* Flush received frame that created FIFO overflow */
  ETH_InitStruct->ETH_FlushReceivedFrame = ETH_FlushReceivedFrame_Enable;
  /* Store and forward mode enabled for transmit */
  ETH_InitStruct->ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;
  /* Threshold TXFIFO level set to 64 bytes (used when threshold mode is enabled) */
  ETH_InitStruct->ETH_TransmitThresholdControl = ETH_TransmitThresholdControl_64Bytes;
  /* Disable forwarding frames with errors (short frames, CRC,...)*/
  ETH_InitStruct->ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;
  /* Disable undersized good frames */
  ETH_InitStruct->ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;
  /* Threshold RXFIFO level set to 64 bytes (used when Cut through mode is enabled) */
  ETH_InitStruct->ETH_ReceiveThresholdControl = ETH_ReceiveThresholdControl_64Bytes;
  /* Disable Operate on second frame (transmit a second frame to FIFO without
  waiting status of previous frame*/
  ETH_InitStruct->ETH_SecondFrameOperate = ETH_SecondFrameOperate_Disable;
  /* DMA works on 32-bit aligned start source and destinations addresses */
  ETH_InitStruct->ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;
  /* Enabled Fixed Burst Mode (mix of INC4, INC8, INC16 and SINGLE DMA transactions */
  ETH_InitStruct->ETH_FixedBurst = ETH_FixedBurst_Enable;
  /* DMA transfer max burst length = 32 beats = 32 x 32bits */
  ETH_InitStruct->ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;
  ETH_InitStruct->ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;
  /* DMA Ring mode skip length = 0 */
  ETH_InitStruct->ETH_DescriptorSkipLength = 0x0;
  /* Equal priority (round-robin) between transmit and receive DMA engines */
  ETH_InitStruct->ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_1_1;
}