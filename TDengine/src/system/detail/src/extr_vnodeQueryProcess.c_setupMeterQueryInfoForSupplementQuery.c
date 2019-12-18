#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_5__ {size_t numOfMeters; int /*<<< orphan*/  rawEKey; int /*<<< orphan*/  rawSKey; TYPE_1__* pMeterDataInfo; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pMeterQInfo; } ;
typedef  TYPE_2__ SMeterQuerySupportObj ;
typedef  int /*<<< orphan*/  SMeterQueryInfo ;

/* Variables and functions */
 int /*<<< orphan*/  changeMeterQueryInfoForSuppleQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setupMeterQueryInfoForSupplementQuery(SMeterQuerySupportObj *pSupporter) {
  for (int32_t i = 0; i < pSupporter->numOfMeters; ++i) {
    SMeterQueryInfo *pMeterQueryInfo = pSupporter->pMeterDataInfo[i].pMeterQInfo;
    changeMeterQueryInfoForSuppleQuery(pMeterQueryInfo, pSupporter->rawSKey, pSupporter->rawEKey);
  }
}