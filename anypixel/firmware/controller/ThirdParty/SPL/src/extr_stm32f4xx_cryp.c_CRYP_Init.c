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
struct TYPE_5__ {int /*<<< orphan*/  CR; } ;
struct TYPE_4__ {int /*<<< orphan*/  CRYP_AlgoDir; int /*<<< orphan*/  CRYP_KeySize; int /*<<< orphan*/  CRYP_AlgoMode; int /*<<< orphan*/  CRYP_DataType; } ;
typedef  TYPE_1__ CRYP_InitTypeDef ;

/* Variables and functions */
 TYPE_3__* CRYP ; 
 int /*<<< orphan*/  CRYP_AlgoMode_AES_CBC ; 
 int /*<<< orphan*/  CRYP_AlgoMode_AES_CTR ; 
 int /*<<< orphan*/  CRYP_AlgoMode_AES_ECB ; 
 int /*<<< orphan*/  CRYP_AlgoMode_AES_Key ; 
 int /*<<< orphan*/  CRYP_CR_ALGODIR ; 
 int /*<<< orphan*/  CRYP_CR_ALGOMODE ; 
 int /*<<< orphan*/  CRYP_CR_DATATYPE ; 
 int /*<<< orphan*/  CRYP_CR_KEYSIZE ; 
 int /*<<< orphan*/  IS_CRYP_ALGODIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_CRYP_ALGOMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_CRYP_DATATYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_CRYP_KEYSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CRYP_Init(CRYP_InitTypeDef* CRYP_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_CRYP_ALGOMODE(CRYP_InitStruct->CRYP_AlgoMode));
  assert_param(IS_CRYP_DATATYPE(CRYP_InitStruct->CRYP_DataType));
  assert_param(IS_CRYP_ALGODIR(CRYP_InitStruct->CRYP_AlgoDir));

  /* Select Algorithm mode*/  
  CRYP->CR &= ~CRYP_CR_ALGOMODE;
  CRYP->CR |= CRYP_InitStruct->CRYP_AlgoMode;

  /* Select dataType */ 
  CRYP->CR &= ~CRYP_CR_DATATYPE;
  CRYP->CR |= CRYP_InitStruct->CRYP_DataType;

  /* select Key size (used only with AES algorithm) */
  if ((CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_ECB) ||
      (CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_CBC) ||
      (CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_CTR) ||
      (CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_Key))
  {
    assert_param(IS_CRYP_KEYSIZE(CRYP_InitStruct->CRYP_KeySize));
    CRYP->CR &= ~CRYP_CR_KEYSIZE;
    CRYP->CR |= CRYP_InitStruct->CRYP_KeySize; /* Key size and value must be 
                                                  configured once the key has 
                                                  been prepared */
  }

  /* Select data Direction */ 
  CRYP->CR &= ~CRYP_CR_ALGODIR;
  CRYP->CR |= CRYP_InitStruct->CRYP_AlgoDir;
}