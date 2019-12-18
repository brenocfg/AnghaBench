#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  ADC_ScanDirection; int /*<<< orphan*/  ADC_DataAlign; int /*<<< orphan*/  ADC_ExternalTrigConvEdge; int /*<<< orphan*/  ADC_ContinuousConvMode; int /*<<< orphan*/  ADC_Resolution; } ;
struct TYPE_6__ {int DMA_BufferSize; int /*<<< orphan*/  DMA_M2M; int /*<<< orphan*/  DMA_Priority; int /*<<< orphan*/  DMA_Mode; int /*<<< orphan*/  DMA_MemoryDataSize; int /*<<< orphan*/  DMA_PeripheralDataSize; int /*<<< orphan*/  DMA_MemoryInc; int /*<<< orphan*/  DMA_PeripheralInc; int /*<<< orphan*/  DMA_DIR; void* DMA_MemoryBaseAddr; void* DMA_PeripheralBaseAddr; } ;
typedef  TYPE_1__ DMA_InitTypeDef ;
typedef  TYPE_2__ ADC_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1 ; 
 int /*<<< orphan*/  ADC_ChannelConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_Channel_0 ; 
 int /*<<< orphan*/  ADC_Channel_1 ; 
 int /*<<< orphan*/  ADC_Channel_2 ; 
 int /*<<< orphan*/  ADC_Channel_3 ; 
 int /*<<< orphan*/  ADC_Channel_4 ; 
 int /*<<< orphan*/  ADC_Channel_5 ; 
 int /*<<< orphan*/  ADC_Channel_6 ; 
 int /*<<< orphan*/  ADC_Channel_7 ; 
 int /*<<< orphan*/  ADC_Channel_8 ; 
 int /*<<< orphan*/  ADC_Channel_9 ; 
 int /*<<< orphan*/  ADC_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_DMACmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_DMAMode_Circular ; 
 int /*<<< orphan*/  ADC_DMARequestModeConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ADC_DMA_ADDR ; 
 int /*<<< orphan*/  ADC_DataAlign_Right ; 
 int /*<<< orphan*/  ADC_ExternalTrigConvEdge_None ; 
 int /*<<< orphan*/  ADC_FLAG_ADRDY ; 
 int /*<<< orphan*/  ADC_GetCalibrationFactor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_GetFlagStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_Init (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ADC_PINS_NUM ; 
 int /*<<< orphan*/  ADC_POWER_AHB ; 
 int /*<<< orphan*/  ADC_POWER_APB1 ; 
 int /*<<< orphan*/  ADC_POWER_APB2 ; 
 int /*<<< orphan*/  ADC_Resolution_12b ; 
 int /*<<< orphan*/  ADC_SampleTime_239_5Cycles ; 
 int /*<<< orphan*/  ADC_ScanDirection_Upward ; 
 int /*<<< orphan*/  ADC_StartOfConversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_StructInit (TYPE_2__*) ; 
 int /*<<< orphan*/  CONFIG_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA1_Channel1 ; 
 int /*<<< orphan*/  DMA_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_DIR_PeripheralSRC ; 
 int /*<<< orphan*/  DMA_DeInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_Init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DMA_M2M_Disable ; 
 int /*<<< orphan*/  DMA_MemoryDataSize_HalfWord ; 
 int /*<<< orphan*/  DMA_MemoryInc_Enable ; 
 int /*<<< orphan*/  DMA_Mode_Circular ; 
 int /*<<< orphan*/  DMA_PeripheralDataSize_HalfWord ; 
 int /*<<< orphan*/  DMA_PeripheralInc_Disable ; 
 int /*<<< orphan*/  DMA_Priority_High ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  RCC_AHBPeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB1PeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB2PeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ adc_readings ; 
 int /*<<< orphan*/  pins_adc ; 

void ANALOG_Config(void) {
    ADC_InitTypeDef adci;
    DMA_InitTypeDef dmai;

    // Enable clocks
    RCC_AHBPeriphClockCmd(ADC_POWER_AHB, ENABLE);
    RCC_APB1PeriphClockCmd(ADC_POWER_APB1, ENABLE);
	RCC_APB2PeriphClockCmd(ADC_POWER_APB2, ENABLE);

    // Configure the pins as analog inputs
    CONFIG_pins(pins_adc, ADC_PINS_NUM);

    // configure ADC
    ADC_StructInit(&adci);
    adci.ADC_Resolution = ADC_Resolution_12b;
    adci.ADC_ContinuousConvMode = ENABLE;
    adci.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    adci.ADC_DataAlign = ADC_DataAlign_Right;
    adci.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &adci);

    // configure channels
    ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_2, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_3, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_5, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_6, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_7, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_8, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_9, ADC_SampleTime_239_5Cycles);

    // get calibration
    ADC_GetCalibrationFactor(ADC1);

    // Set up DMA for circular buffer mode
    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);

    ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(ADC1, ENABLE);

    // wait for the ADRDY flag is set
    while( !ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));

    ADC_StartOfConversion(ADC1);

    DMA_DeInit(DMA1_Channel1);
    dmai.DMA_PeripheralBaseAddr = (uint32_t)ADC_DMA_ADDR;
    dmai.DMA_MemoryBaseAddr = (uint32_t)adc_readings;
    dmai.DMA_DIR = DMA_DIR_PeripheralSRC;
    dmai.DMA_BufferSize = 10;
    dmai.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dmai.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dmai.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dmai.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dmai.DMA_Mode = DMA_Mode_Circular;
    dmai.DMA_Priority = DMA_Priority_High;
    dmai.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &dmai);
    DMA_Cmd(DMA1_Channel1, ENABLE);
}