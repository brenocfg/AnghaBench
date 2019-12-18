#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_22__ {int* elemSize; char** data; size_t numOfCols; scalar_t__ offset; TYPE_3__* pExpr; } ;
struct TYPE_21__ {size_t colIdxInBuf; size_t colIdx; int /*<<< orphan*/  colId; int /*<<< orphan*/  flag; } ;
struct TYPE_20__ {int bytes; int /*<<< orphan*/  type; int /*<<< orphan*/  colId; } ;
struct TYPE_19__ {size_t startOffset; int inputBytes; int /*<<< orphan*/  inputType; } ;
struct TYPE_18__ {size_t pos; size_t numOfCols; TYPE_3__* pSelectExpr; TYPE_1__* colList; } ;
struct TYPE_17__ {TYPE_6__* pCtx; TYPE_5__* pQuery; } ;
struct TYPE_15__ {size_t functionId; TYPE_8__ colInfo; } ;
struct TYPE_16__ {TYPE_2__ pBase; } ;
struct TYPE_14__ {size_t colIdxInBuf; size_t colIdx; TYPE_7__ data; } ;
typedef  TYPE_4__ SQueryRuntimeEnv ;
typedef  TYPE_5__ SQuery ;
typedef  TYPE_6__ SQLFunctionCtx ;
typedef  TYPE_7__ SColumnInfo ;
typedef  TYPE_8__ SColIndexEx ;
typedef  TYPE_9__ SArithmeticSupport ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_5__*) ; 
 scalar_t__ TSDB_COL_IS_TAG (int /*<<< orphan*/ ) ; 
 size_t TSDB_FUNC_ARITHM ; 
 char* doGetDataBlocks (int,TYPE_4__*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 

__attribute__((used)) static char *getDataBlocks(SQueryRuntimeEnv *pRuntimeEnv, char *data, SArithmeticSupport *sas, int32_t col,
                           int32_t size, bool isDiskFileBlock) {
  SQuery *        pQuery = pRuntimeEnv->pQuery;
  SQLFunctionCtx *pCtx = pRuntimeEnv->pCtx;

  char *dataBlock = NULL;

  int32_t functionId = pQuery->pSelectExpr[col].pBase.functionId;

  if (functionId == TSDB_FUNC_ARITHM) {
    sas->pExpr = &pQuery->pSelectExpr[col];

    // set the start offset to be the lowest start position, no matter asc/desc query order
    if (QUERY_IS_ASC_QUERY(pQuery)) {
      pCtx->startOffset = pQuery->pos;
    } else {
      pCtx->startOffset = pQuery->pos - (size - 1);
    }

    for (int32_t i = 0; i < pQuery->numOfCols; ++i) {
      int32_t colIdx = isDiskFileBlock ? pQuery->colList[i].colIdxInBuf : pQuery->colList[i].colIdx;

      SColumnInfo *pColMsg = &pQuery->colList[i].data;
      char *       pData = doGetDataBlocks(isDiskFileBlock, pRuntimeEnv, data, colIdx, pColMsg->colId, pColMsg->type,
                                    pColMsg->bytes, pQuery->colList[i].colIdxInBuf);

      sas->elemSize[i] = pColMsg->bytes;
      sas->data[i] = pData + pCtx->startOffset * sas->elemSize[i];  // start from the offset
    }
    sas->numOfCols = pQuery->numOfCols;
    sas->offset = 0;
  } else {  // other type of query function
    SColIndexEx *pCol = &pQuery->pSelectExpr[col].pBase.colInfo;
    int32_t      colIdx = isDiskFileBlock ? pCol->colIdxInBuf : pCol->colIdx;

    if (TSDB_COL_IS_TAG(pCol->flag)) {
      dataBlock = NULL;
    } else {
      /*
       *  the colIdx is acquired from the first meter of all qualified meters in this vnode during query prepare stage,
       *  the remain meter may not have the required column in cache actually.
       *  So, the validation of required column in cache with the corresponding meter schema is reinforced.
       */
      dataBlock = doGetDataBlocks(isDiskFileBlock, pRuntimeEnv, data, colIdx, pCol->colId, pCtx[col].inputType,
                                  pCtx[col].inputBytes, pCol->colIdxInBuf);
    }
  }

  return dataBlock;
}