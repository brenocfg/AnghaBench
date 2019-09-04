#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  K3RR; int /*<<< orphan*/  K3LR; int /*<<< orphan*/  K2RR; int /*<<< orphan*/  K2LR; int /*<<< orphan*/  K1RR; int /*<<< orphan*/  K1LR; int /*<<< orphan*/  K0RR; int /*<<< orphan*/  K0LR; } ;
struct TYPE_4__ {int /*<<< orphan*/  CRYP_Key3Right; int /*<<< orphan*/  CRYP_Key3Left; int /*<<< orphan*/  CRYP_Key2Right; int /*<<< orphan*/  CRYP_Key2Left; int /*<<< orphan*/  CRYP_Key1Right; int /*<<< orphan*/  CRYP_Key1Left; int /*<<< orphan*/  CRYP_Key0Right; int /*<<< orphan*/  CRYP_Key0Left; } ;
typedef  TYPE_1__ CRYP_KeyInitTypeDef ;

/* Variables and functions */
 TYPE_3__* CRYP ; 

void CRYP_KeyInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct)
{
  /* Key Initialisation */
  CRYP->K0LR = CRYP_KeyInitStruct->CRYP_Key0Left;
  CRYP->K0RR = CRYP_KeyInitStruct->CRYP_Key0Right;
  CRYP->K1LR = CRYP_KeyInitStruct->CRYP_Key1Left;
  CRYP->K1RR = CRYP_KeyInitStruct->CRYP_Key1Right;
  CRYP->K2LR = CRYP_KeyInitStruct->CRYP_Key2Left;
  CRYP->K2RR = CRYP_KeyInitStruct->CRYP_Key2Right;
  CRYP->K3LR = CRYP_KeyInitStruct->CRYP_Key3Left;
  CRYP->K3RR = CRYP_KeyInitStruct->CRYP_Key3Right;
}