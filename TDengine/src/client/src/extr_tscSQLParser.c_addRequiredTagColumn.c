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
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int numOfTags; scalar_t__* tagColumnIndex; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_1__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ TSDB_MAX_TAGS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 TYPE_1__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,scalar_t__) ; 

void addRequiredTagColumn(SSqlCmd* pCmd, int32_t tagColIndex, int32_t tableIndex) {
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, tableIndex);

  if (pMeterMetaInfo->numOfTags == 0 || pMeterMetaInfo->tagColumnIndex[pMeterMetaInfo->numOfTags - 1] < tagColIndex) {
    pMeterMetaInfo->tagColumnIndex[pMeterMetaInfo->numOfTags++] = tagColIndex;
  } else {  // find the appropriate position
    for (int32_t i = 0; i < pMeterMetaInfo->numOfTags; ++i) {
      if (tagColIndex > pMeterMetaInfo->tagColumnIndex[i]) {
        continue;
      } else if (tagColIndex == pMeterMetaInfo->tagColumnIndex[i]) {
        break;
      } else {
        memmove(&pMeterMetaInfo->tagColumnIndex[i + 1], &pMeterMetaInfo->tagColumnIndex[i],
                sizeof(pMeterMetaInfo->tagColumnIndex[0]) * (pMeterMetaInfo->numOfTags - i));

        pMeterMetaInfo->tagColumnIndex[i] = tagColIndex;

        pMeterMetaInfo->numOfTags++;
        break;
      }
    }
  }

  // plus one means tbname
  assert(tagColIndex >= -1 && tagColIndex < TSDB_MAX_TAGS && pMeterMetaInfo->numOfTags <= TSDB_MAX_TAGS + 1);
}