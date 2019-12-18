#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numOfElems; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ tFilePage ;
typedef  int int32_t ;
struct TYPE_10__ {TYPE_1__* pResultBuf; } ;
struct TYPE_8__ {int qhandle; TYPE_4__* pLocalReducer; int /*<<< orphan*/  data; scalar_t__ rspType; scalar_t__ row; scalar_t__ numOfRows; } ;
struct TYPE_9__ {TYPE_2__ res; } ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SLocalReducer ;

/* Variables and functions */
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  tscDestroyLocalReducer (TYPE_3__*) ; 

void tscInitResObjForLocalQuery(SSqlObj *pObj, int32_t numOfRes, int32_t rowLen) {
  SSqlRes *pRes = &pObj->res;
  if (pRes->pLocalReducer != NULL) {
    tscDestroyLocalReducer(pObj);
  }

  pRes->qhandle = 1;  // hack to pass the safety check in fetch_row function
  pRes->numOfRows = 0;
  pRes->row = 0;

  pRes->rspType = 0;  // used as a flag to denote if taos_retrieved() has been called yet
  pRes->pLocalReducer = (SLocalReducer *)calloc(1, sizeof(SLocalReducer));

  /*
   * we need one additional byte space
   * the sprintf function needs one additional space to put '\0' at the end of string
   */
  size_t allocSize = numOfRes * rowLen + sizeof(tFilePage) + 1;
  pRes->pLocalReducer->pResultBuf = (tFilePage *)calloc(1, allocSize);

  pRes->pLocalReducer->pResultBuf->numOfElems = numOfRes;
  pRes->data = pRes->pLocalReducer->pResultBuf->data;
}