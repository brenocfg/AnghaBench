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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ CR; } ;

/* Variables and functions */
 TYPE_1__* CRC ; 
 scalar_t__ CRC_CR_POLSIZE ; 
 int /*<<< orphan*/  IS_CRC_POL_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CRC_PolynomialSizeSelect(uint32_t CRC_PolSize)
{
  uint32_t tmpcr = 0;

  /* Check the parameter */
  assert_param(IS_CRC_POL_SIZE(CRC_PolSize));

  /* Get CR register value */
  tmpcr = CRC->CR;

  /* Reset POL_SIZE bits */
  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_POLSIZE);
  /* Set the polynomial size */
  tmpcr |= (uint32_t)CRC_PolSize;

  /* Write to CR register */
  CRC->CR = (uint32_t)tmpcr;
}