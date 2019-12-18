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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int DMA_PeripheralBaseAddr; int DMA_MemoryBaseAddr; int /*<<< orphan*/  DMA_DIR; int /*<<< orphan*/  DMA_M2M; int /*<<< orphan*/  DMA_Priority; int /*<<< orphan*/  DMA_Mode; int /*<<< orphan*/  DMA_MemoryDataSize; int /*<<< orphan*/  DMA_PeripheralDataSize; int /*<<< orphan*/  DMA_MemoryInc; int /*<<< orphan*/  DMA_PeripheralInc; int /*<<< orphan*/  DMA_BufferSize; } ;
typedef  TYPE_1__ DMA_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  DMA_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_DIR_PeripheralDST ; 
 int /*<<< orphan*/  DMA_DIR_PeripheralSRC ; 
 int /*<<< orphan*/  DMA_Init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DMA_M2M_Disable ; 
 int /*<<< orphan*/  DMA_MemoryDataSize_Byte ; 
 int /*<<< orphan*/  DMA_MemoryInc_Enable ; 
 int /*<<< orphan*/  DMA_Mode_Normal ; 
 int /*<<< orphan*/  DMA_PeripheralDataSize_Byte ; 
 int /*<<< orphan*/  DMA_PeripheralInc_Disable ; 
 int /*<<< orphan*/  DMA_Priority_Medium ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  SPI_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_I2S_DMACmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int SPI_I2S_DMAReq_Rx ; 
 int SPI_I2S_DMAReq_Tx ; 
 scalar_t__ TLC59401_DMA_DR ; 
 int /*<<< orphan*/  TLC59401_RX_DMA ; 
 int /*<<< orphan*/  TLC59401_SPI ; 
 int /*<<< orphan*/  TLC59401_TX_DMA ; 
 int /*<<< orphan*/  isIdle (int /*<<< orphan*/ ) ; 
 int needLatch0 ; 
 int needLatch1 ; 

__attribute__((used)) static bool Start_DMA_Transfer(uint8_t* dataOut, uint8_t* dataIn, uint16_t count) {
    DMA_InitTypeDef DMA_InitStruct;
    // first make sure the device isn't busy and that any previous transmissions have been latched
    if( !isIdle(TLC59401_SPI) || needLatch0 || needLatch1)
        return false;

    // disable things while we configure them
    SPI_Cmd(TLC59401_SPI, DISABLE);
    DMA_Cmd(TLC59401_TX_DMA, DISABLE);
    DMA_Cmd(TLC59401_RX_DMA, DISABLE);

    // Idle, so set up DMA TX transfer
    DMA_InitStruct.DMA_PeripheralBaseAddr = (int)TLC59401_DMA_DR;
    DMA_InitStruct.DMA_MemoryBaseAddr = (int)dataOut;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStruct.DMA_BufferSize = count;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(TLC59401_TX_DMA, &DMA_InitStruct);

    // changed the relevant fields for RX transfer
    DMA_InitStruct.DMA_MemoryBaseAddr = (int)dataIn;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_Init(TLC59401_RX_DMA, &DMA_InitStruct);

    DMA_Cmd(TLC59401_TX_DMA, ENABLE);
    DMA_Cmd(TLC59401_RX_DMA, ENABLE);

    SPI_I2S_DMACmd(TLC59401_SPI,SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, ENABLE);

    SPI_Cmd(TLC59401_SPI, ENABLE);

    needLatch0 = true;
    needLatch1 = true;

    return true;
}