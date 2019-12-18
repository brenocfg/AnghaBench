#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_8__ {int numOfTags; int /*<<< orphan*/  tagColumnIndex; int /*<<< orphan*/ * pMetricMeta; int /*<<< orphan*/ * pMeterMeta; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int numOfTables; TYPE_2__** pMeterInfo; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  int /*<<< orphan*/  SMetricMeta ;
typedef  TYPE_2__ SMeterMetaInfo ;
typedef  int /*<<< orphan*/  SMeterMeta ;

/* Variables and functions */
 int POINTER_BYTES ; 
 scalar_t__ TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 void* realloc (TYPE_2__**,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

SMeterMetaInfo* tscAddMeterMetaInfo(SSqlCmd* pCmd, const char* name, SMeterMeta* pMeterMeta, SMetricMeta* pMetricMeta,
                                    int16_t numOfTags, int16_t* tags) {
  void* pAlloc = realloc(pCmd->pMeterInfo, (pCmd->numOfTables + 1) * POINTER_BYTES);
  if (pAlloc == NULL) {
    return NULL;
  }

  pCmd->pMeterInfo = pAlloc;
  pCmd->pMeterInfo[pCmd->numOfTables] = calloc(1, sizeof(SMeterMetaInfo));

  SMeterMetaInfo* pMeterMetaInfo = pCmd->pMeterInfo[pCmd->numOfTables];
  assert(pMeterMetaInfo != NULL);

  if (name != NULL) {
    assert(strlen(name) <= TSDB_METER_ID_LEN);
    strcpy(pMeterMetaInfo->name, name);
  }

  pMeterMetaInfo->pMeterMeta = pMeterMeta;
  pMeterMetaInfo->pMetricMeta = pMetricMeta;
  pMeterMetaInfo->numOfTags = numOfTags;

  if (tags != NULL) {
    memcpy(pMeterMetaInfo->tagColumnIndex, tags, sizeof(int16_t) * numOfTags);
  }

  pCmd->numOfTables += 1;

  return pMeterMetaInfo;
}