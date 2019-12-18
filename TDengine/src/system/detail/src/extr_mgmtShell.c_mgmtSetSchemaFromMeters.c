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
typedef  int uint32_t ;
struct TYPE_6__ {void* colId; void* bytes; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ schema; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 void* htons (void*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgmtSetSchemaFromMeters(SSchema *pSchema, STabObj *pMeterObj, uint32_t numOfCols) {
  SSchema *pMeterSchema = (SSchema *)(pMeterObj->schema);
  for (int i = 0; i < numOfCols; ++i) {
    pSchema->type = pMeterSchema[i].type;
    strcpy(pSchema->name, pMeterSchema[i].name);
    pSchema->bytes = htons(pMeterSchema[i].bytes);
    pSchema->colId = htons(pMeterSchema[i].colId);
    pSchema++;
  }
}