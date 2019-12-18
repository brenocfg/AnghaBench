#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_14__ {scalar_t__ i64Key; } ;
struct TYPE_21__ {scalar_t__ aInputElemBuf; TYPE_1__ tag; } ;
struct TYPE_16__ {int /*<<< orphan*/  order; } ;
struct TYPE_20__ {TYPE_3__ order; } ;
struct TYPE_19__ {TYPE_10__* pTSBuf; TYPE_2__* pMeterObj; TYPE_8__* pCtx; TYPE_7__* pQuery; } ;
struct TYPE_18__ {scalar_t__ tag; scalar_t__ ts; } ;
struct TYPE_17__ {int /*<<< orphan*/  tsIndex; int /*<<< orphan*/  order; } ;
struct TYPE_15__ {int /*<<< orphan*/  meterId; } ;
struct TYPE_13__ {TYPE_4__ cur; int /*<<< orphan*/  tsOrder; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_5__ STSElem ;
typedef  TYPE_6__ SQueryRuntimeEnv ;
typedef  TYPE_7__ SQuery ;
typedef  TYPE_8__ SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_7__*) ; 
 int TSDB_KEYSIZE ; 
 int TS_JOIN_TAG_NOT_EQUALS ; 
 int TS_JOIN_TS_EQUAL ; 
 int TS_JOIN_TS_NOT_EQUALS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ tsBufGetElem (TYPE_10__*) ; 

__attribute__((used)) static int32_t doTSJoinFilter(SQueryRuntimeEnv *pRuntimeEnv, int32_t offset) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  STSElem         elem = tsBufGetElem(pRuntimeEnv->pTSBuf);
  SQLFunctionCtx *pCtx = pRuntimeEnv->pCtx;

  // compare tag first
  if (pCtx[0].tag.i64Key != elem.tag) {
    return TS_JOIN_TAG_NOT_EQUALS;
  }

  TSKEY key = *(TSKEY *)(pCtx[0].aInputElemBuf + TSDB_KEYSIZE * offset);

#if 1
  printf("elem in comp ts file:%lld, key:%lld, tag:%d, id:%s, query order:%d, ts order:%d, traverse:%d, index:%d\n",
         elem.ts, key, elem.tag, pRuntimeEnv->pMeterObj->meterId, pQuery->order.order, pRuntimeEnv->pTSBuf->tsOrder,
         pRuntimeEnv->pTSBuf->cur.order, pRuntimeEnv->pTSBuf->cur.tsIndex);
#endif

  if (QUERY_IS_ASC_QUERY(pQuery)) {
    if (key < elem.ts) {
      return TS_JOIN_TS_NOT_EQUALS;
    } else if (key > elem.ts) {
      assert(false);
    }
  } else {
    if (key > elem.ts) {
      return TS_JOIN_TS_NOT_EQUALS;
    } else if (key < elem.ts) {
      assert(false);
    }
  }

  return TS_JOIN_TS_EQUAL;
}