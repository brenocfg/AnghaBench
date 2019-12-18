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
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int numOfTags; int numOfColumns; scalar_t__ schema; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 int /*<<< orphan*/  mgmtIsMetric (TYPE_1__*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int32_t mgmtFindTagCol(STabObj *pMetric, const char *tagName) {
  if (!mgmtIsMetric(pMetric)) return -1;

  SSchema *schema = NULL;

  for (int i = 0; i < pMetric->numOfTags; i++) {
    schema = (SSchema *)(pMetric->schema + (pMetric->numOfColumns + i) * sizeof(SSchema));

    if (strcasecmp(tagName, schema->name) == 0) return i;
  }

  return -1;
}