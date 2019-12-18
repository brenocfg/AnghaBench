#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_4__ {int nAlloc; int /*<<< orphan*/ * pData; } ;
typedef  TYPE_1__ SDataBlockList ;

/* Variables and functions */
 int POINTER_BYTES ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

SDataBlockList* tscCreateBlockArrayList() {
  const int32_t DEFAULT_INITIAL_NUM_OF_BLOCK = 16;

  SDataBlockList* pDataBlockArrayList = calloc(1, sizeof(SDataBlockList));
  if (pDataBlockArrayList == NULL) {
    return NULL;
  }
  pDataBlockArrayList->nAlloc = DEFAULT_INITIAL_NUM_OF_BLOCK;
  pDataBlockArrayList->pData = calloc(1, POINTER_BYTES * pDataBlockArrayList->nAlloc);
  if (pDataBlockArrayList->pData == NULL) {
    free(pDataBlockArrayList);
    return NULL;
  }

  return pDataBlockArrayList;
}