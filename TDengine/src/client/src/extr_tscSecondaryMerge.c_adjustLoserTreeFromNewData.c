#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_13__ {scalar_t__ numOfElems; } ;
struct TYPE_17__ {scalar_t__ rowIdx; TYPE_1__ filePage; } ;
struct TYPE_16__ {scalar_t__ numOfBuffer; } ;
struct TYPE_15__ {TYPE_2__* pNode; } ;
struct TYPE_14__ {scalar_t__ index; } ;
typedef  TYPE_3__ SLoserTreeInfo ;
typedef  TYPE_4__ SLocalReducer ;
typedef  TYPE_5__ SLocalDataSource ;

/* Variables and functions */
 int /*<<< orphan*/  loadNewDataFromDiskFor (TYPE_4__*,TYPE_5__*,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tLoserTreeAdjust (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  tLoserTreeDisplay (TYPE_3__*) ; 

void adjustLoserTreeFromNewData(SLocalReducer *pLocalReducer, SLocalDataSource *pOneInterDataSrc,
                                SLoserTreeInfo *pTree) {
  /*
   * load a new data page into memory for intermediate dataset source,
   * since it's last record in buffer has been chosen to be processed, as the winner of loser-tree
   */
  bool needToAdjust = true;
  if (pOneInterDataSrc->filePage.numOfElems <= pOneInterDataSrc->rowIdx) {
    loadNewDataFromDiskFor(pLocalReducer, pOneInterDataSrc, &needToAdjust);
  }

  /*
   * adjust loser tree otherwise, according to new candidate data
   * if the loser tree is rebuild completed, we do not need to adjust
   */
  if (needToAdjust) {
    int32_t leafNodeIdx = pTree->pNode[0].index + pLocalReducer->numOfBuffer;

#ifdef _DEBUG_VIEW
    printf("before adjust:\t");
    tLoserTreeDisplay(pTree);
#endif

    tLoserTreeAdjust(pTree, leafNodeIdx);

#ifdef _DEBUG_VIEW
    printf("\nafter adjust:\t");
    tLoserTreeDisplay(pTree);
    printf("\n");
#endif
  }
}