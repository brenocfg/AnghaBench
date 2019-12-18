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
typedef  int uint32_t ;
struct TYPE_7__ {int I2C_DigitalFilter; int I2C_Mode; int I2C_Ack; int I2C_Timing; scalar_t__ I2C_OwnAddress1; scalar_t__ I2C_AcknowledgedAddress; scalar_t__ I2C_AnalogFilter; } ;
struct TYPE_6__ {int CR1; int TIMINGR; int OAR1; int OAR2; int CR2; } ;
typedef  TYPE_1__ I2C_TypeDef ;
typedef  TYPE_2__ I2C_InitTypeDef ;

/* Variables and functions */
 int CR1_CLEAR_MASK ; 
 int CR2_CLEAR_MASK ; 
 int I2C_CR1_PE ; 
 int I2C_OAR1_OA1EN ; 
 int /*<<< orphan*/  IS_I2C_ACK (int) ; 
 int /*<<< orphan*/  IS_I2C_ACKNOWLEDGE_ADDRESS (scalar_t__) ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_I2C_ANALOG_FILTER (scalar_t__) ; 
 int /*<<< orphan*/  IS_I2C_DIGITAL_FILTER (int) ; 
 int /*<<< orphan*/  IS_I2C_MODE (int) ; 
 int /*<<< orphan*/  IS_I2C_OWN_ADDRESS1 (scalar_t__) ; 
 int TIMING_CLEAR_MASK ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_ANALOG_FILTER(I2C_InitStruct->I2C_AnalogFilter));
  assert_param(IS_I2C_DIGITAL_FILTER(I2C_InitStruct->I2C_DigitalFilter));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
  assert_param(IS_I2C_ACK(I2C_InitStruct->I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress));

  /* Disable I2Cx Peripheral */
  I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PE);

  /*---------------------------- I2Cx FILTERS Configuration ------------------*/
  /* Get the I2Cx CR1 value */
  tmpreg = I2Cx->CR1;
  /* Clear I2Cx CR1 register */
  tmpreg &= CR1_CLEAR_MASK;
  /* Configure I2Cx: analog and digital filter */
  /* Set ANFOFF bit according to I2C_AnalogFilter value */
  /* Set DFN bits according to I2C_DigitalFilter value */
  tmpreg |= (uint32_t)I2C_InitStruct->I2C_AnalogFilter |(I2C_InitStruct->I2C_DigitalFilter << 8);

  /* Write to I2Cx CR1 */
  I2Cx->CR1 = tmpreg;

  /*---------------------------- I2Cx TIMING Configuration -------------------*/
  /* Configure I2Cx: Timing */
  /* Set TIMINGR bits according to I2C_Timing */
  /* Write to I2Cx TIMING */
  I2Cx->TIMINGR = I2C_InitStruct->I2C_Timing & TIMING_CLEAR_MASK;

  /* Enable I2Cx Peripheral */
  I2Cx->CR1 |= I2C_CR1_PE;

  /*---------------------------- I2Cx OAR1 Configuration ---------------------*/
  /* Clear tmpreg local variable */
  tmpreg = 0;
  /* Clear OAR1 register */
  I2Cx->OAR1 = (uint32_t)tmpreg;
  /* Clear OAR2 register */
  I2Cx->OAR2 = (uint32_t)tmpreg;
  /* Configure I2Cx: Own Address1 and acknowledged address */
  /* Set OA1MODE bit according to I2C_AcknowledgedAddress value */
  /* Set OA1 bits according to I2C_OwnAddress1 value */
  tmpreg = (uint32_t)((uint32_t)I2C_InitStruct->I2C_AcknowledgedAddress | \
                      (uint32_t)I2C_InitStruct->I2C_OwnAddress1);
  /* Write to I2Cx OAR1 */
  I2Cx->OAR1 = tmpreg;
  /* Enable Own Address1 acknowledgement */
  I2Cx->OAR1 |= I2C_OAR1_OA1EN;

  /*---------------------------- I2Cx MODE Configuration ---------------------*/
  /* Configure I2Cx: mode */
  /* Set SMBDEN and SMBHEN bits according to I2C_Mode value */
  tmpreg = I2C_InitStruct->I2C_Mode;
  /* Write to I2Cx CR1 */
  I2Cx->CR1 |= tmpreg;

  /*---------------------------- I2Cx ACK Configuration ----------------------*/
  /* Get the I2Cx CR2 value */
  tmpreg = I2Cx->CR2;
  /* Clear I2Cx CR2 register */
  tmpreg &= CR2_CLEAR_MASK;
  /* Configure I2Cx: acknowledgement */
  /* Set NACK bit according to I2C_Ack value */
  tmpreg |= I2C_InitStruct->I2C_Ack;
  /* Write to I2Cx CR2 */
  I2Cx->CR2 = tmpreg;
}