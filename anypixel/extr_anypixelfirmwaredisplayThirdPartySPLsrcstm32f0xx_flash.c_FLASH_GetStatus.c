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
struct TYPE_2__ {int SR; } ;
typedef  int /*<<< orphan*/  FLASH_Status ;

/* Variables and functions */
 TYPE_1__* FLASH ; 
 int /*<<< orphan*/  FLASH_BUSY ; 
 int /*<<< orphan*/  FLASH_COMPLETE ; 
 int /*<<< orphan*/  FLASH_ERROR_PROGRAM ; 
 int /*<<< orphan*/  FLASH_ERROR_WRP ; 
 int FLASH_FLAG_BSY ; 
 scalar_t__ FLASH_FLAG_WRPERR ; 
 scalar_t__ FLASH_SR_PGERR ; 

FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status FLASHstatus = FLASH_COMPLETE;
  
  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  {
    FLASHstatus = FLASH_BUSY;
  }
  else 
  {  
    if((FLASH->SR & (uint32_t)FLASH_FLAG_WRPERR)!= (uint32_t)0x00)
    { 
      FLASHstatus = FLASH_ERROR_WRP;
    }
    else 
    {
      if((FLASH->SR & (uint32_t)(FLASH_SR_PGERR)) != (uint32_t)0x00)
      {
        FLASHstatus = FLASH_ERROR_PROGRAM; 
      }
      else
      {
        FLASHstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the FLASH Status */
  return FLASHstatus;
}