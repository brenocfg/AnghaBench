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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  CFGR; } ;

/* Variables and functions */
 TYPE_1__* CRS ; 
 int /*<<< orphan*/  CRS_CFGR_SYNCPOL ; 
 int /*<<< orphan*/  IS_CRS_SYNC_POLARITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CRS_SynchronizationPolarityConfig(uint32_t CRS_Polarity)
{
  /* Check the parameters */
  assert_param(IS_CRS_SYNC_POLARITY(CRS_Polarity));
  
  /* Clear SYNCSPOL bit */
  CRS->CFGR &= ~CRS_CFGR_SYNCPOL;
  
  /* Set the SYNCSPOL bits according to CRS_Polarity value */
  CRS->CFGR |= CRS_Polarity;
}