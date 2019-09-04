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

void HASH_SaveContext(HASH_Context* HASH_ContextSave)
{
  uint8_t i = 0;
  
  /* save context registers */
  HASH_ContextSave->HASH_IMR = HASH->IMR;  
  HASH_ContextSave->HASH_STR = HASH->STR;      
  HASH_ContextSave->HASH_CR  = HASH->CR;     
  for(i=0; i<=50;i++)
  {
     HASH_ContextSave->HASH_CSR[i] = HASH->CSR[i];
  }   
}