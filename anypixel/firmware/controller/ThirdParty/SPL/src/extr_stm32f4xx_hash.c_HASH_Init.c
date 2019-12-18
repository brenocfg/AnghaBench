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
struct TYPE_5__ {int CR; } ;
struct TYPE_4__ {int HASH_AlgoSelection; int HASH_DataType; int HASH_AlgoMode; int HASH_HMACKeyType; } ;
typedef  TYPE_1__ HASH_InitTypeDef ;

/* Variables and functions */
 TYPE_3__* HASH ; 
 int HASH_AlgoMode_HMAC ; 
 int HASH_CR_ALGO ; 
 int HASH_CR_DATATYPE ; 
 int HASH_CR_INIT ; 
 int HASH_CR_LKEY ; 
 int HASH_CR_MODE ; 
 int /*<<< orphan*/  IS_HASH_ALGOMODE (int) ; 
 int /*<<< orphan*/  IS_HASH_ALGOSELECTION (int) ; 
 int /*<<< orphan*/  IS_HASH_DATATYPE (int) ; 
 int /*<<< orphan*/  IS_HASH_HMAC_KEYTYPE (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void HASH_Init(HASH_InitTypeDef* HASH_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_HASH_ALGOSELECTION(HASH_InitStruct->HASH_AlgoSelection));
  assert_param(IS_HASH_DATATYPE(HASH_InitStruct->HASH_DataType));
  assert_param(IS_HASH_ALGOMODE(HASH_InitStruct->HASH_AlgoMode));
  
  /* Configure the Algorithm used, algorithm mode and the datatype */
  HASH->CR &= ~ (HASH_CR_ALGO | HASH_CR_DATATYPE | HASH_CR_MODE);
  HASH->CR |= (HASH_InitStruct->HASH_AlgoSelection | \
               HASH_InitStruct->HASH_DataType | \
               HASH_InitStruct->HASH_AlgoMode);
  
  /* if algorithm mode is HMAC, set the Key */  
  if(HASH_InitStruct->HASH_AlgoMode == HASH_AlgoMode_HMAC) 
  {
    assert_param(IS_HASH_HMAC_KEYTYPE(HASH_InitStruct->HASH_HMACKeyType));
    HASH->CR &= ~HASH_CR_LKEY;
    HASH->CR |= HASH_InitStruct->HASH_HMACKeyType;
  }

  /* Reset the HASH processor core, so that the HASH will be ready to compute 
     the message digest of a new message */
  HASH->CR |= HASH_CR_INIT;  
}