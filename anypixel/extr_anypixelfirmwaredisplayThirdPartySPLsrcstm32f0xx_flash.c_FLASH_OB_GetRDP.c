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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int OBR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 TYPE_1__* FLASH ; 
 int FLASH_OBR_RDPRT1 ; 
 int FLASH_OBR_RDPRT2 ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 

FlagStatus FLASH_OB_GetRDP(void)
{
  FlagStatus readstatus = RESET;
  
  if ((uint8_t)(FLASH->OBR & (FLASH_OBR_RDPRT1 | FLASH_OBR_RDPRT2)) != RESET)
  {
    readstatus = SET;
  }
  else
  {
    readstatus = RESET;
  }
  return readstatus;
}