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
typedef  int uint16_t ;
struct TYPE_7__ {int GPIO_Pin; scalar_t__ GPIO_Mode; scalar_t__ GPIO_PuPd; scalar_t__ GPIO_OType; scalar_t__ GPIO_Speed; } ;
struct TYPE_6__ {int OSPEEDR; int OTYPER; int MODER; int PUPDR; } ;
typedef  TYPE_1__ GPIO_TypeDef ;
typedef  TYPE_2__ GPIO_InitTypeDef ;

/* Variables and functions */
 int GPIO_MODER_MODER0 ; 
 scalar_t__ GPIO_Mode_AF ; 
 scalar_t__ GPIO_Mode_OUT ; 
 int GPIO_OSPEEDER_OSPEEDR0 ; 
 int GPIO_OTYPER_OT_0 ; 
 int GPIO_PUPDR_PUPDR0 ; 
 int /*<<< orphan*/  IS_GPIO_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_GPIO_MODE (scalar_t__) ; 
 int /*<<< orphan*/  IS_GPIO_OTYPE (scalar_t__) ; 
 int /*<<< orphan*/  IS_GPIO_PIN (int) ; 
 int /*<<< orphan*/  IS_GPIO_PUPD (scalar_t__) ; 
 int /*<<< orphan*/  IS_GPIO_SPEED (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /*-------------------------- Configure the port pins -----------------------*/
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;

    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration */
        GPIOx->OTYPER &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos));
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));

      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      /* Pull-up Pull down resistor configuration */
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}