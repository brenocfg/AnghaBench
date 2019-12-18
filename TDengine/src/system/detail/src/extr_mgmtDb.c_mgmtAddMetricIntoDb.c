#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  numOfMetrics; TYPE_1__* pMetric; } ;
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SDbObj ;

/* Variables and functions */

int mgmtAddMetricIntoDb(SDbObj *pDb, STabObj *pMetric) {
  pMetric->next = pDb->pMetric;
  pMetric->prev = NULL;

  if (pDb->pMetric) pDb->pMetric->prev = pMetric;

  pDb->pMetric = pMetric;
  pDb->numOfMetrics++;

  return 0;
}