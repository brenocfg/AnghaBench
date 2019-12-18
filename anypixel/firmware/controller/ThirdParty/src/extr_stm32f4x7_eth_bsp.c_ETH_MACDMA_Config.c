#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ETH_DMAArbitration; int /*<<< orphan*/  ETH_TxDMABurstLength; int /*<<< orphan*/  ETH_RxDMABurstLength; int /*<<< orphan*/  ETH_FixedBurst; int /*<<< orphan*/  ETH_AddressAlignedBeats; int /*<<< orphan*/  ETH_SecondFrameOperate; int /*<<< orphan*/  ETH_ForwardUndersizedGoodFrames; int /*<<< orphan*/  ETH_ForwardErrorFrames; int /*<<< orphan*/  ETH_TransmitStoreForward; int /*<<< orphan*/  ETH_ReceiveStoreForward; int /*<<< orphan*/  ETH_DropTCPIPChecksumErrorFrame; int /*<<< orphan*/  ETH_ChecksumOffload; int /*<<< orphan*/  ETH_UnicastFramesFilter; int /*<<< orphan*/  ETH_MulticastFramesFilter; int /*<<< orphan*/  ETH_PromiscuousMode; int /*<<< orphan*/  ETH_BroadcastFramesReception; int /*<<< orphan*/  ETH_ReceiveAll; int /*<<< orphan*/  ETH_AutomaticPadCRCStrip; int /*<<< orphan*/  ETH_RetryTransmission; int /*<<< orphan*/  ETH_LoopbackMode; int /*<<< orphan*/  ETH_AutoNegotiation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  ETH_AddressAlignedBeats_Enable ; 
 int /*<<< orphan*/  ETH_AutoNegotiation_Enable ; 
 int /*<<< orphan*/  ETH_AutomaticPadCRCStrip_Disable ; 
 int /*<<< orphan*/  ETH_BroadcastFramesReception_Enable ; 
 int /*<<< orphan*/  ETH_ChecksumOffload_Enable ; 
 int /*<<< orphan*/  ETH_DMAArbitration_RoundRobin_RxTx_2_1 ; 
 int /*<<< orphan*/  ETH_DeInit () ; 
 int /*<<< orphan*/  ETH_DropTCPIPChecksumErrorFrame_Enable ; 
 scalar_t__ ETH_ERROR ; 
 int /*<<< orphan*/  ETH_FixedBurst_Enable ; 
 int /*<<< orphan*/  ETH_ForwardErrorFrames_Disable ; 
 int /*<<< orphan*/  ETH_ForwardUndersizedGoodFrames_Disable ; 
 scalar_t__ ETH_GetSoftwareResetStatus () ; 
 scalar_t__ ETH_Init (TYPE_1__*,int) ; 
 TYPE_1__ ETH_InitStructure ; 
 int /*<<< orphan*/  ETH_LoopbackMode_Disable ; 
 int /*<<< orphan*/  ETH_MulticastFramesFilter_Perfect ; 
 int /*<<< orphan*/  ETH_PromiscuousMode_Disable ; 
 int /*<<< orphan*/  ETH_ReceiveAll_Disable ; 
 int /*<<< orphan*/  ETH_ReceiveStoreForward_Enable ; 
 int /*<<< orphan*/  ETH_RetryTransmission_Disable ; 
 int /*<<< orphan*/  ETH_RxDMABurstLength_32Beat ; 
 int /*<<< orphan*/  ETH_SecondFrameOperate_Enable ; 
 int /*<<< orphan*/  ETH_SoftwareReset () ; 
 int /*<<< orphan*/  ETH_StructInit (TYPE_1__*) ; 
 int /*<<< orphan*/  ETH_TransmitStoreForward_Enable ; 
 int /*<<< orphan*/  ETH_TxDMABurstLength_32Beat ; 
 int /*<<< orphan*/  ETH_UnicastFramesFilter_Perfect ; 
 scalar_t__ EthStatus ; 
 int /*<<< orphan*/  RCC_AHB1PeriphClockCmd (int,int /*<<< orphan*/ ) ; 
 int RCC_AHB1Periph_ETH_MAC ; 
 int RCC_AHB1Periph_ETH_MAC_Rx ; 
 int RCC_AHB1Periph_ETH_MAC_Tx ; 
 scalar_t__ SET ; 

__attribute__((used)) static void ETH_MACDMA_Config(void)
{
  /* Enable ETHERNET clock  */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC | RCC_AHB1Periph_ETH_MAC_Tx |
                        RCC_AHB1Periph_ETH_MAC_Rx, ENABLE);

  /* Reset ETHERNET on AHB Bus */
  ETH_DeInit();

  /* Software reset */
  ETH_SoftwareReset();

  /* Wait for software reset */
  while (ETH_GetSoftwareResetStatus() == SET);

  /* ETHERNET Configuration --------------------------------------------------*/
  /* Call ETH_StructInit if you don't like to configure all ETH_InitStructure parameter */
  ETH_StructInit(&ETH_InitStructure);

  /* Fill ETH_InitStructure parametrs */
  /*------------------------   MAC   -----------------------------------*/
  ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;
//  ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Disable;
//  ETH_InitStructure.ETH_Speed = ETH_Speed_10M;
//  ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;

  ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
  ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable;
  ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;
  ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;
  ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;
  ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;
  ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;
  ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;
#ifdef CHECKSUM_BY_HARDWARE
  ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable;
#endif

  /*------------------------   DMA   -----------------------------------*/

  /* When we use the Checksum offload feature, we need to enable the Store and Forward mode:
  the store and forward guarantee that a whole frame is stored in the FIFO, so the MAC can insert/verify the checksum,
  if the checksum is OK the DMA can handle the frame otherwise the frame is dropped */
  ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable;
  ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;
  ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;

  ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;
  ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;
  ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Enable;
  ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;
  ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;
  ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;
  ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;
  ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_2_1;

  /* Configure Ethernet */
  EthStatus = ETH_Init(&ETH_InitStructure, 1);
  if(EthStatus == ETH_ERROR)
     EthStatus = ETH_Init(&ETH_InitStructure, 2);
}