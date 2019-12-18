#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* meterList; int /*<<< orphan*/ * idPool; } ;
typedef  TYPE_1__ SVgObj ;

/* Variables and functions */
 int /*<<< orphan*/  taosIdPoolCleanUp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (void*) ; 

void *mgmtVgroupActionDestroy(void *row, char *str, int size, int *ssize) {
  SVgObj *pVgroup = (SVgObj *)row;
  if (pVgroup->idPool) {
    taosIdPoolCleanUp(pVgroup->idPool);
    pVgroup->idPool = NULL;
  }
  if (pVgroup->meterList) tfree(pVgroup->meterList);
  tfree(row);
  return NULL;
}