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
struct TYPE_3__ {int SPI_CRCPolynomial; int /*<<< orphan*/  SPI_FirstBit; int /*<<< orphan*/  SPI_BaudRatePrescaler; int /*<<< orphan*/  SPI_NSS; int /*<<< orphan*/  SPI_CPHA; int /*<<< orphan*/  SPI_CPOL; int /*<<< orphan*/  SPI_DataSize; int /*<<< orphan*/  SPI_Mode; int /*<<< orphan*/  SPI_Direction; } ;
typedef  TYPE_1__ SPI_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_BaudRatePrescaler_2 ; 
 int /*<<< orphan*/  SPI_CPHA_1Edge ; 
 int /*<<< orphan*/  SPI_CPOL_Low ; 
 int /*<<< orphan*/  SPI_DataSize_8b ; 
 int /*<<< orphan*/  SPI_Direction_2Lines_FullDuplex ; 
 int /*<<< orphan*/  SPI_FirstBit_MSB ; 
 int /*<<< orphan*/  SPI_Mode_Slave ; 
 int /*<<< orphan*/  SPI_NSS_Hard ; 

void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
/*--------------- Reset SPI init structure parameters values -----------------*/
  /* Initialize the SPI_Direction member */
  SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  /* Initialize the SPI_Mode member */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
  /* Initialize the SPI_DataSize member */
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  /* Initialize the SPI_CPOL member */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  /* Initialize the SPI_CPHA member */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  /* Initialize the SPI_NSS member */
  SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  /* Initialize the SPI_FirstBit member */
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
  /* Initialize the SPI_CRCPolynomial member */
  SPI_InitStruct->SPI_CRCPolynomial = 7;
}