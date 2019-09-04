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
struct TYPE_3__ {int /*<<< orphan*/  GPIO_PuPd; int /*<<< orphan*/  GPIO_OType; int /*<<< orphan*/  GPIO_Speed; int /*<<< orphan*/  GPIO_Mode; int /*<<< orphan*/  GPIO_Pin; } ;
typedef  TYPE_1__ GPIO_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_Mode_IN ; 
 int /*<<< orphan*/  GPIO_OType_PP ; 
 int /*<<< orphan*/  GPIO_Pin_All ; 
 int /*<<< orphan*/  GPIO_PuPd_NOPULL ; 
 int /*<<< orphan*/  GPIO_Speed_Level_2 ; 

void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}