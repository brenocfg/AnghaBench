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
struct TYPE_2__ {int MACSR; } ;
typedef  scalar_t__ ITStatus ;

/* Variables and functions */
 TYPE_1__* ETH ; 
 int /*<<< orphan*/  IS_ETH_MAC_GET_IT (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus ETH_GetMACITStatus(uint32_t ETH_MAC_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ETH_MAC_GET_IT(ETH_MAC_IT));
  if ((ETH->MACSR & ETH_MAC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}