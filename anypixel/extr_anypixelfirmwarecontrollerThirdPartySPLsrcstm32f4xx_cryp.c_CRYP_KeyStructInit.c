#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ CRYP_Key3Right; scalar_t__ CRYP_Key3Left; scalar_t__ CRYP_Key2Right; scalar_t__ CRYP_Key2Left; scalar_t__ CRYP_Key1Right; scalar_t__ CRYP_Key1Left; scalar_t__ CRYP_Key0Right; scalar_t__ CRYP_Key0Left; } ;
typedef  TYPE_1__ CRYP_KeyInitTypeDef ;

/* Variables and functions */

void CRYP_KeyStructInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct)
{
  CRYP_KeyInitStruct->CRYP_Key0Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key0Right = 0;
  CRYP_KeyInitStruct->CRYP_Key1Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key1Right = 0;
  CRYP_KeyInitStruct->CRYP_Key2Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key2Right = 0;
  CRYP_KeyInitStruct->CRYP_Key3Left  = 0;
  CRYP_KeyInitStruct->CRYP_Key3Right = 0;
}