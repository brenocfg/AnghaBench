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
struct TYPE_3__ {int /*<<< orphan*/  CRYP_KeySize; int /*<<< orphan*/  CRYP_DataType; int /*<<< orphan*/  CRYP_AlgoMode; int /*<<< orphan*/  CRYP_AlgoDir; } ;
typedef  TYPE_1__ CRYP_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_AlgoDir_Encrypt ; 
 int /*<<< orphan*/  CRYP_AlgoMode_TDES_ECB ; 
 int /*<<< orphan*/  CRYP_DataType_32b ; 
 int /*<<< orphan*/  CRYP_KeySize_128b ; 

void CRYP_StructInit(CRYP_InitTypeDef* CRYP_InitStruct)
{
  /* Initialize the CRYP_AlgoDir member */
  CRYP_InitStruct->CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;

  /* initialize the CRYP_AlgoMode member */
  CRYP_InitStruct->CRYP_AlgoMode = CRYP_AlgoMode_TDES_ECB;

  /* initialize the CRYP_DataType member */
  CRYP_InitStruct->CRYP_DataType = CRYP_DataType_32b;
  
  /* Initialize the CRYP_KeySize member */
  CRYP_InitStruct->CRYP_KeySize = CRYP_KeySize_128b;
}