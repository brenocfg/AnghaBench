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
 int /*<<< orphan*/  CRS_CFGR_SYNCSRC ; 
 int /*<<< orphan*/  IS_CRS_SYNC_SOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CRS_SynchronizationSourceConfig(uint32_t CRS_Source)
{
  /* Check the parameters */
  assert_param(IS_CRS_SYNC_SOURCE(CRS_Source));
  
  /* Clear SYNCSRC[1:0] bits */
  CRS->CFGR &= ~CRS_CFGR_SYNCSRC;
  
  /* Set the SYNCSRC[1:0] bits according to CRS_Source value */
  CRS->CFGR |= CRS_Source;
}