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
struct TYPE_3__ {int /*<<< orphan*/  HASH_HMACKeyType; int /*<<< orphan*/  HASH_DataType; int /*<<< orphan*/  HASH_AlgoMode; int /*<<< orphan*/  HASH_AlgoSelection; } ;
typedef  TYPE_1__ HASH_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_AlgoMode_HASH ; 
 int /*<<< orphan*/  HASH_AlgoSelection_SHA1 ; 
 int /*<<< orphan*/  HASH_DataType_32b ; 
 int /*<<< orphan*/  HASH_HMACKeyType_ShortKey ; 

void HASH_StructInit(HASH_InitTypeDef* HASH_InitStruct)
{
  /* Initialize the HASH_AlgoSelection member */
  HASH_InitStruct->HASH_AlgoSelection = HASH_AlgoSelection_SHA1;

  /* Initialize the HASH_AlgoMode member */
  HASH_InitStruct->HASH_AlgoMode = HASH_AlgoMode_HASH;

  /* Initialize the HASH_DataType member */
  HASH_InitStruct->HASH_DataType = HASH_DataType_32b;

  /* Initialize the HASH_HMACKeyType member */
  HASH_InitStruct->HASH_HMACKeyType = HASH_HMACKeyType_ShortKey;
}