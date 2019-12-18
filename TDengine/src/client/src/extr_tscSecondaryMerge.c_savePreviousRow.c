#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numOfElems; scalar_t__ data; } ;
typedef  TYPE_3__ tFilePage ;
struct TYPE_11__ {int maxCapacity; size_t numOfCols; TYPE_1__* pFields; scalar_t__* colOffset; } ;
typedef  TYPE_4__ tColModel ;
typedef  size_t int32_t ;
struct TYPE_12__ {int hasPrevRow; scalar_t__ prevRowOfInput; TYPE_2__* pDesc; } ;
struct TYPE_9__ {TYPE_4__* pSchema; } ;
struct TYPE_8__ {int /*<<< orphan*/  bytes; } ;
typedef  TYPE_5__ SLocalReducer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void savePreviousRow(SLocalReducer *pLocalReducer, tFilePage *tmpBuffer) {
  tColModel *pColModel = pLocalReducer->pDesc->pSchema;
  assert(pColModel->maxCapacity == 1 && tmpBuffer->numOfElems == 1);

  // copy to previous temp buffer
  for (int32_t i = 0; i < pLocalReducer->pDesc->pSchema->numOfCols; ++i) {
    memcpy(pLocalReducer->prevRowOfInput + pColModel->colOffset[i], tmpBuffer->data + pColModel->colOffset[i],
           pColModel->pFields[i].bytes);
  }

  tmpBuffer->numOfElems = 0;
  pLocalReducer->hasPrevRow = true;
}