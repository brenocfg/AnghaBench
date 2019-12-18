#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  colId; int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {scalar_t__ colNameList; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  colId; int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SSchema ;
typedef  TYPE_2__ SQueryMeterMsg ;
typedef  TYPE_3__ SColumnInfo ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static SSchema* toSchema(SQueryMeterMsg* pQuery, SColumnInfo* pCols, int32_t numOfCols) {
  char* start = (char*)pQuery->colNameList;
  char* end = start;

  SSchema* pSchema = calloc(1, sizeof(SSchema) * numOfCols);
  for (int32_t i = 0; i < numOfCols; ++i) {
    pSchema[i].type = pCols[i].type;
    pSchema[i].bytes = pCols[i].bytes;
    pSchema[i].colId = pCols[i].colId;

    end = strstr(start, ",");
    memcpy(pSchema[i].name, start, end - start);
    start = end + 1;
  }

  return pSchema;
}