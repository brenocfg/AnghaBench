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
struct TYPE_2__ {int ISR; } ;
typedef  int /*<<< orphan*/  FlagStatus ;

/* Variables and functions */
 TYPE_1__* CRS ; 
 int /*<<< orphan*/  IS_CRS_FLAG (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus CRS_GetFlagStatus(uint32_t CRS_FLAG)
{
  /* Check the parameters */
  assert_param(IS_CRS_FLAG(CRS_FLAG));

  return ((FlagStatus)(CRS->ISR & CRS_FLAG));
}