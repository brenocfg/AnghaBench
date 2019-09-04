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
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * CSR; int /*<<< orphan*/  CR; int /*<<< orphan*/  STR; int /*<<< orphan*/  IMR; } ;
struct TYPE_4__ {int /*<<< orphan*/ * HASH_CSR; int /*<<< orphan*/  HASH_CR; int /*<<< orphan*/  HASH_STR; int /*<<< orphan*/  HASH_IMR; } ;
typedef  TYPE_1__ HASH_Context ;

/* Variables and functions */
 TYPE_3__* HASH ; 
 int /*<<< orphan*/  HASH_CR_INIT ; 

void HASH_RestoreContext(HASH_Context* HASH_ContextRestore)  
{
  uint8_t i = 0;
  
  /* restore context registers */
  HASH->IMR = HASH_ContextRestore->HASH_IMR;   
  HASH->STR = HASH_ContextRestore->HASH_STR;     
  HASH->CR = HASH_ContextRestore->HASH_CR;
  
  /* Initialize the hash processor */
  HASH->CR |= HASH_CR_INIT; 
  
   /* continue restoring context registers */     
  for(i=0; i<=50;i++)
  {
     HASH->CSR[i] = HASH_ContextRestore->HASH_CSR[i];
  }   
}