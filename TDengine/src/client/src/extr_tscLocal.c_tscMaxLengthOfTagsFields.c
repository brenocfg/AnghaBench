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
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_12__ {TYPE_3__* pMeterMeta; } ;
struct TYPE_11__ {scalar_t__ meterType; size_t numOfTags; } ;
struct TYPE_10__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlObj ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SMeterMeta ;

/* Variables and functions */
 scalar_t__ TSDB_METER_METRIC ; 
 scalar_t__ TSDB_METER_OTABLE ; 
 scalar_t__ TSDB_METER_STABLE ; 
 size_t getToStringLength (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tsGetTagSchema (TYPE_3__*) ; 
 char* tsGetTagsValue (TYPE_3__*) ; 
 TYPE_5__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t tscMaxLengthOfTagsFields(SSqlObj *pSql) {
  SMeterMeta *pMeta = tscGetMeterMetaInfo(&pSql->cmd, 0)->pMeterMeta;

  if (pMeta->meterType == TSDB_METER_METRIC || pMeta->meterType == TSDB_METER_OTABLE ||
      pMeta->meterType == TSDB_METER_STABLE) {
    return 0;
  }

  char *   pTagValue = tsGetTagsValue(pMeta);
  SSchema *pTagsSchema = tsGetTagSchema(pMeta);

  int32_t len = getToStringLength(pTagValue, pTagsSchema[0].bytes, pTagsSchema[0].type);

  pTagValue += pTagsSchema[0].bytes;
  for (int32_t i = 1; i < pMeta->numOfTags; ++i) {
    int32_t tLen = getToStringLength(pTagValue, pTagsSchema[i].bytes, pTagsSchema[i].type);
    if (len < tLen) {
      len = tLen;
    }

    pTagValue += pTagsSchema[i].bytes;
  }

  return len;
}