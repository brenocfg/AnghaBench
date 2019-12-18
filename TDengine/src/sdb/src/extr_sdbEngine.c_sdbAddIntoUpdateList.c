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
struct TYPE_5__ {int numOfUpdates; int updatePos; int maxRows; TYPE_1__* update; int /*<<< orphan*/  (* appTool ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {char type; char* row; } ;
typedef  TYPE_2__ SSdbTable ;

/* Variables and functions */
 char SDB_TYPE_DELETE ; 
 int /*<<< orphan*/  SDB_TYPE_DESTROY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sdbAddIntoUpdateList(SSdbTable *pTable, char type, char *row) {
  pTable->numOfUpdates++;
  pTable->updatePos = pTable->numOfUpdates % pTable->maxRows;

  if (pTable->update[pTable->updatePos].type == SDB_TYPE_DELETE)
    (*(pTable->appTool))(SDB_TYPE_DESTROY, pTable->update[pTable->updatePos].row, NULL, 0, NULL);

  pTable->update[pTable->updatePos].type = type;
  pTable->update[pTable->updatePos].row = row;
}