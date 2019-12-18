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
typedef  int uint32_t ;
struct TYPE_2__ {int PLLI2SCFGR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_PLLI2SN_VALUE (int) ; 
 int /*<<< orphan*/  IS_RCC_PLLI2SR_VALUE (int) ; 
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_PLLI2SConfig(uint32_t PLLI2SN, uint32_t PLLI2SR)
{
  /* Check the parameters */
  assert_param(IS_RCC_PLLI2SN_VALUE(PLLI2SN));
  assert_param(IS_RCC_PLLI2SR_VALUE(PLLI2SR));

  RCC->PLLI2SCFGR = (PLLI2SN << 6) | (PLLI2SR << 28);
}