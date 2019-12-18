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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tFilePage ;
struct TYPE_3__ {int numOfPages; int numOfAlloc; int /*<<< orphan*/ * pageList; } ;
typedef  int /*<<< orphan*/  SMeterQuerySupportObj ;
typedef  TYPE_1__ SMeterQueryInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * allocNewPage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

tFilePage *addDataPageForMeterQueryInfo(SMeterQueryInfo *pMeterQueryInfo, SMeterQuerySupportObj *pSupporter) {
  uint32_t   pageId = 0;
  tFilePage *pPage = allocNewPage(pSupporter, &pageId);

  if (pMeterQueryInfo->numOfPages >= pMeterQueryInfo->numOfAlloc) {
    pMeterQueryInfo->numOfAlloc = pMeterQueryInfo->numOfAlloc << 1;
    pMeterQueryInfo->pageList = realloc(pMeterQueryInfo->pageList, sizeof(uint32_t) * pMeterQueryInfo->numOfAlloc);
  }

  pMeterQueryInfo->pageList[pMeterQueryInfo->numOfPages++] = pageId;
  return pPage;
}