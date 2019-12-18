#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num; TYPE_2__** pRes; } ;
typedef  TYPE_1__ tQueryResultset ;
typedef  int int32_t ;
struct TYPE_10__ {scalar_t__ meterType; char* pTagData; scalar_t__ uid; int /*<<< orphan*/  meterId; } ;
typedef  TYPE_2__ STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_METER_ID_LEN ; 
 scalar_t__ TSDB_METER_MTABLE ; 
 int /*<<< orphan*/  mWarn (char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__** malloc (int) ; 
 TYPE_2__* mgmtGetMeter (char*) ; 
 TYPE_2__** realloc (TYPE_2__**,int) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char const*) ; 

__attribute__((used)) static void mgmtRetrieveByMeterName(tQueryResultset* pRes, char* str, STabObj* pMetric) {
  const char* sep = ",";
  char*       pToken = NULL;

  int32_t s = 4;  // initial size

  pRes->pRes = malloc(sizeof(char*) * s);
  pRes->num = 0;

  for (pToken = strsep(&str, sep); pToken != NULL; pToken = strsep(&str, sep)) {
    STabObj* pMeterObj = mgmtGetMeter(pToken);
    if (pMeterObj == NULL) {
      mWarn("metric:%s error in metric query expression, invalid meter id:%s", pMetric->meterId, pToken);
      continue;
    }

    if (pRes->num >= s) {
      s += (s >> 1);  // increase 50% size
      pRes->pRes = realloc(pRes->pRes, sizeof(char*) * s);
    }

    /* not a table created from metric, ignore */
    if (pMeterObj->meterType != TSDB_METER_MTABLE) {
      continue;
    }

    /*
     * queried meter not belongs to this metric, ignore, metric does not have
     * uid, so compare according to meterid
     */
    STabObj* parentMetric = mgmtGetMeter(pMeterObj->pTagData);
    if (strncasecmp(parentMetric->meterId, pMetric->meterId, TSDB_METER_ID_LEN) != 0 ||
        (parentMetric->uid != pMetric->uid)) {
      continue;
    }

    pRes->pRes[pRes->num++] = pMeterObj;
  }
}