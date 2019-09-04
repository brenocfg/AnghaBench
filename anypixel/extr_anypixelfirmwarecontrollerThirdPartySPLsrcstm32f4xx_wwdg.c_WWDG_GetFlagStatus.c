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
struct TYPE_2__ {scalar_t__ SR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 TYPE_1__* WWDG ; 

FlagStatus WWDG_GetFlagStatus(void)
{
  FlagStatus bitstatus = RESET;
    
  if ((WWDG->SR) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}