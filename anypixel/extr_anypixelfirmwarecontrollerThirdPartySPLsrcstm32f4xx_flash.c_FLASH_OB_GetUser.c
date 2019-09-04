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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int OPTCR; } ;

/* Variables and functions */
 TYPE_1__* FLASH ; 

uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)(FLASH->OPTCR >> 5);
}