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
struct TYPE_5__ {int /*<<< orphan*/  IV1RR; int /*<<< orphan*/  IV1LR; int /*<<< orphan*/  IV0RR; int /*<<< orphan*/  IV0LR; } ;
struct TYPE_4__ {int /*<<< orphan*/  CRYP_IV1Right; int /*<<< orphan*/  CRYP_IV1Left; int /*<<< orphan*/  CRYP_IV0Right; int /*<<< orphan*/  CRYP_IV0Left; } ;
typedef  TYPE_1__ CRYP_IVInitTypeDef ;

/* Variables and functions */
 TYPE_3__* CRYP ; 

void CRYP_IVInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct)
{
  CRYP->IV0LR = CRYP_IVInitStruct->CRYP_IV0Left;
  CRYP->IV0RR = CRYP_IVInitStruct->CRYP_IV0Right;
  CRYP->IV1LR = CRYP_IVInitStruct->CRYP_IV1Left;
  CRYP->IV1RR = CRYP_IVInitStruct->CRYP_IV1Right;
}