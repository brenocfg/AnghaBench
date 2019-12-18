#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  __merge_compare_fn_t ;
struct TYPE_6__ {int numOfEntries; int totalEntries; int /*<<< orphan*/  comparaFn; void* param; int /*<<< orphan*/ * pNode; } ;
typedef  int /*<<< orphan*/  SLoserTreeNode ;
typedef  TYPE_1__ SLoserTreeInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  TSDB_CODE_SUCCESS ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  pError (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tLoserTreeAdjust (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tLoserTreeDisplay (TYPE_1__*) ; 
 int /*<<< orphan*/  tLoserTreeInit (TYPE_1__*) ; 

uint8_t tLoserTreeCreate(SLoserTreeInfo** pTree, int32_t numOfEntries, void* param, __merge_compare_fn_t compareFn) {
  int32_t totalEntries = numOfEntries << 1;

  *pTree = (SLoserTreeInfo*)calloc(1, sizeof(SLoserTreeInfo) + sizeof(SLoserTreeNode) * totalEntries);
  if ((*pTree) == NULL) {
    pError("allocate memory for losertree failed. out of memory");
    return TSDB_CODE_CLI_OUT_OF_MEMORY;
  }

  (*pTree)->pNode = (SLoserTreeNode*)(((char*)(*pTree)) + sizeof(SLoserTreeInfo));

  (*pTree)->numOfEntries = numOfEntries;
  (*pTree)->totalEntries = totalEntries;
  (*pTree)->param = param;
  (*pTree)->comparaFn = compareFn;

  // set initial value for loser tree
  tLoserTreeInit(*pTree);

#ifdef _DEBUG_VIEW
  printf("the initial value of loser tree:\n");
  tLoserTreeDisplay(*pTree);
#endif

  for (int32_t i = totalEntries - 1; i >= numOfEntries; i--) {
    tLoserTreeAdjust(*pTree, i);
  }

#if defined(_DEBUG_VIEW)
  printf("after adjust:\n");
  tLoserTreeDisplay(*pTree);
  printf("initialize local reducer completed!\n");
#endif

  return TSDB_CODE_SUCCESS;
}