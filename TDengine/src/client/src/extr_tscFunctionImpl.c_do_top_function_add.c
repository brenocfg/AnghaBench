#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_15__ {scalar_t__ i64Key; scalar_t__ dKey; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ tVariant ;
struct TYPE_14__ {scalar_t__ i64Key; scalar_t__ dKey; } ;
struct TYPE_16__ {TYPE_1__ v; } ;
typedef  TYPE_3__ tValuePair ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_19__ {int /*<<< orphan*/  nSize; } ;
struct TYPE_18__ {int /*<<< orphan*/  tagsLen; } ;
struct TYPE_17__ {size_t num; TYPE_3__** res; } ;
typedef  TYPE_4__ STopBotInfo ;
typedef  TYPE_5__ SExtTagsInfo ;

/* Variables and functions */
 size_t TSDB_DATA_TYPE_BIGINT ; 
 size_t TSDB_DATA_TYPE_DOUBLE ; 
 size_t TSDB_DATA_TYPE_FLOAT ; 
 size_t TSDB_DATA_TYPE_TINYINT ; 
 int /*<<< orphan*/  VALUEPAIRASSIGN (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* tDataTypeDesc ; 
 int /*<<< orphan*/  tVariantCreateFromBinary (TYPE_2__*,void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  valuePairAssign (TYPE_3__*,size_t,scalar_t__*,int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_top_function_add(STopBotInfo *pInfo, int32_t maxLen, void *pData, int64_t ts, uint16_t type,
                                SExtTagsInfo *pTagInfo, char *pTags, int16_t stage) {
  tVariant val = {0};
  tVariantCreateFromBinary(&val, pData, tDataTypeDesc[type].nSize, type);

  tValuePair **pList = pInfo->res;

  if (pInfo->num < maxLen) {
    if (pInfo->num == 0 ||
        ((type >= TSDB_DATA_TYPE_TINYINT && type <= TSDB_DATA_TYPE_BIGINT) &&
         val.i64Key >= pList[pInfo->num - 1]->v.i64Key) ||
        ((type >= TSDB_DATA_TYPE_FLOAT && type <= TSDB_DATA_TYPE_DOUBLE) &&
         val.dKey >= pList[pInfo->num - 1]->v.dKey)) {
      valuePairAssign(pList[pInfo->num], type, &val.i64Key, ts, pTags, pTagInfo, stage);
    } else {
      int32_t i = pInfo->num - 1;

      if (type >= TSDB_DATA_TYPE_TINYINT && type <= TSDB_DATA_TYPE_BIGINT) {
        while (i >= 0 && pList[i]->v.i64Key > val.i64Key) {
          VALUEPAIRASSIGN(pList[i + 1], pList[i], pTagInfo->tagsLen);
          i -= 1;
        }
      } else {
        while (i >= 0 && pList[i]->v.dKey > val.dKey) {
          VALUEPAIRASSIGN(pList[i + 1], pList[i], pTagInfo->tagsLen);
          i -= 1;
        }
      }

      valuePairAssign(pList[i + 1], type, &val.i64Key, ts, pTags, pTagInfo, stage);
    }

    pInfo->num++;
  } else {
    int32_t i = 0;

    if (((type >= TSDB_DATA_TYPE_TINYINT && type <= TSDB_DATA_TYPE_BIGINT) && val.i64Key > pList[0]->v.i64Key) ||
        ((type >= TSDB_DATA_TYPE_FLOAT && type <= TSDB_DATA_TYPE_DOUBLE) && val.dKey > pList[0]->v.dKey)) {
      // find the appropriate the slot position
      if (type >= TSDB_DATA_TYPE_TINYINT && type <= TSDB_DATA_TYPE_BIGINT) {
        while (i + 1 < maxLen && pList[i + 1]->v.i64Key < val.i64Key) {
          VALUEPAIRASSIGN(pList[i], pList[i + 1], pTagInfo->tagsLen);
          i += 1;
        }
      } else {
        while (i + 1 < maxLen && pList[i + 1]->v.dKey < val.dKey) {
          VALUEPAIRASSIGN(pList[i], pList[i + 1], pTagInfo->tagsLen);
          i += 1;
        }
      }

      valuePairAssign(pList[i], type, &val.i64Key, ts, pTags, pTagInfo, stage);
    }
  }
}