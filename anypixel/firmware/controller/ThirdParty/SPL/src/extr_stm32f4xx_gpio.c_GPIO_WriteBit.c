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
typedef  void* uint16_t ;
struct TYPE_4__ {void* BSRRH; void* BSRRL; } ;
typedef  TYPE_1__ GPIO_TypeDef ;
typedef  scalar_t__ BitAction ;

/* Variables and functions */
 scalar_t__ Bit_RESET ; 
 int /*<<< orphan*/  IS_GET_GPIO_PIN (void*) ; 
 int /*<<< orphan*/  IS_GPIO_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_GPIO_BIT_ACTION (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRRL = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRRH = GPIO_Pin ;
  }
}