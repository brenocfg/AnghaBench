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
typedef  int /*<<< orphan*/  tSQLExprListList ;
struct TYPE_6__ {int /*<<< orphan*/ * pValue; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  sqlType; TYPE_2__* pInsertInfo; } ;
typedef  TYPE_1__ SSqlInfo ;
typedef  int /*<<< orphan*/  SSQLToken ;
typedef  TYPE_2__ SInsertSQL ;

/* Variables and functions */
 int /*<<< orphan*/  TSQL_INSERT ; 
 TYPE_2__* calloc (int,int) ; 

void tSetInsertSQLElems(SSqlInfo *pInfo, SSQLToken *pName, tSQLExprListList *pList) {
  SInsertSQL *pInsert = calloc(1, sizeof(SInsertSQL));

  pInsert->name = *pName;
  pInsert->pValue = pList;

  pInfo->pInsertInfo = pInsert;
  pInfo->sqlType = TSQL_INSERT;
}