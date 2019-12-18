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
struct TYPE_3__ {char* updateEnd; int schemaSize; struct TYPE_3__* schema; } ;
typedef  TYPE_1__ STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_1__*,int) ; 

void *mgmtMeterActionEncode(void *row, char *str, int size, int *ssize) {
  assert(row != NULL && str != NULL);

  STabObj *pMeter = (STabObj *)row;
  int      tsize = pMeter->updateEnd - (char *)pMeter;

  if (size < tsize + pMeter->schemaSize + 1) {
    *ssize = -1;
    return NULL;
  }

  memcpy(str, pMeter, tsize);
  memcpy(str + tsize, pMeter->schema, pMeter->schemaSize);

  *ssize = tsize + pMeter->schemaSize;

  return NULL;
}