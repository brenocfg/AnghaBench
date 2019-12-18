#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 scalar_t__ ETH_ERROR ; 
 scalar_t__ ETH_ReadPHYRegister (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ETH_SUCCESS ; 
 scalar_t__ ETH_WritePHYRegister (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IS_ETH_PHY_ADDRESS (scalar_t__) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  PHY_BCR ; 
 scalar_t__ PHY_Loopback ; 
 scalar_t__ RESET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint32_t ETH_PHYLoopBackCmd(uint16_t PHYAddress, FunctionalState NewState)
{
  uint16_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ETH_PHY_ADDRESS(PHYAddress));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the PHY configuration to update it */
  tmpreg = ETH_ReadPHYRegister(PHYAddress, PHY_BCR);

  if (NewState != DISABLE)
  {
    /* Enable the PHY loopback mode */
    tmpreg |= PHY_Loopback;
  }
  else
  {
    /* Disable the PHY loopback mode: normal mode */
    tmpreg &= (uint16_t)(~(uint16_t)PHY_Loopback);
  }
  /* Update the PHY control register with the new configuration */
  if(ETH_WritePHYRegister(PHYAddress, PHY_BCR, tmpreg) != (uint32_t)RESET)
  {
    return ETH_SUCCESS;
  }
  else
  {
    /* Return SUCCESS */
    return ETH_ERROR;
  }
}