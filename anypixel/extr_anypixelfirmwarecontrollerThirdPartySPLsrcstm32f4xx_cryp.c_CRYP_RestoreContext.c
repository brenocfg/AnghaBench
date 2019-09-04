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
struct TYPE_5__ {int /*<<< orphan*/  CR; int /*<<< orphan*/  IV1RR; int /*<<< orphan*/  IV1LR; int /*<<< orphan*/  IV0RR; int /*<<< orphan*/  IV0LR; int /*<<< orphan*/  K3RR; int /*<<< orphan*/  K3LR; int /*<<< orphan*/  K2RR; int /*<<< orphan*/  K2LR; int /*<<< orphan*/  K1RR; int /*<<< orphan*/  K1LR; int /*<<< orphan*/  K0RR; int /*<<< orphan*/  K0LR; } ;
struct TYPE_4__ {int /*<<< orphan*/  CRYP_IV1RR; int /*<<< orphan*/  CRYP_IV1LR; int /*<<< orphan*/  CRYP_IV0RR; int /*<<< orphan*/  CRYP_IV0LR; int /*<<< orphan*/  CRYP_K3RR; int /*<<< orphan*/  CRYP_K3LR; int /*<<< orphan*/  CRYP_K2RR; int /*<<< orphan*/  CRYP_K2LR; int /*<<< orphan*/  CRYP_K1RR; int /*<<< orphan*/  CRYP_K1LR; int /*<<< orphan*/  CRYP_K0RR; int /*<<< orphan*/  CRYP_K0LR; int /*<<< orphan*/  CR_bits9to2; } ;
typedef  TYPE_1__ CRYP_Context ;

/* Variables and functions */
 TYPE_3__* CRYP ; 
 int /*<<< orphan*/  CRYP_CR_CRYPEN ; 

void CRYP_RestoreContext(CRYP_Context* CRYP_ContextRestore)  
{

  /* Configure the processor with the saved configuration */
  CRYP->CR = CRYP_ContextRestore->CR_bits9to2;

  /* restore The key value */
  CRYP->K0LR = CRYP_ContextRestore->CRYP_K0LR; 
  CRYP->K0RR = CRYP_ContextRestore->CRYP_K0RR;
  CRYP->K1LR = CRYP_ContextRestore->CRYP_K1LR;
  CRYP->K1RR = CRYP_ContextRestore->CRYP_K1RR;
  CRYP->K2LR = CRYP_ContextRestore->CRYP_K2LR;
  CRYP->K2RR = CRYP_ContextRestore->CRYP_K2RR;
  CRYP->K3LR = CRYP_ContextRestore->CRYP_K3LR;
  CRYP->K3RR = CRYP_ContextRestore->CRYP_K3RR;

  /* and the initialization vectors. */
  CRYP->IV0LR = CRYP_ContextRestore->CRYP_IV0LR;
  CRYP->IV0RR = CRYP_ContextRestore->CRYP_IV0RR;
  CRYP->IV1LR = CRYP_ContextRestore->CRYP_IV1LR;
  CRYP->IV1RR = CRYP_ContextRestore->CRYP_IV1RR;

  /* Enable the cryptographic processor */
  CRYP->CR |= CRYP_CR_CRYPEN;
}