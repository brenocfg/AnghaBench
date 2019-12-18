#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int CFGR; } ;

/* Variables and functions */
 TYPE_1__* CEC ; 
 int /*<<< orphan*/  IS_CEC_ADDRESS (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress)
{
  uint32_t tmp =0x00;
  /* Check the parameters */
  assert_param(IS_CEC_ADDRESS(CEC_OwnAddress));
  tmp = 1 <<(CEC_OwnAddress + 16);
  /* Set the CEC own address */
  CEC->CFGR |= tmp;
}