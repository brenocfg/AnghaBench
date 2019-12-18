#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tVariantList ;
typedef  int /*<<< orphan*/  tFieldList ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * varList; int /*<<< orphan*/ * pAddColumns; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SSQLToken ;
typedef  TYPE_1__ SAlterTableSQL ;

/* Variables and functions */
 scalar_t__ ALTER_TABLE_ADD_COLUMN ; 
 scalar_t__ ALTER_TABLE_TAGS_ADD ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 

SAlterTableSQL *tAlterTableSQLElems(SSQLToken *pMeterName, tFieldList *pCols, tVariantList *pVals, int32_t type) {
  SAlterTableSQL *pAlterTable = calloc(1, sizeof(SAlterTableSQL));
  pAlterTable->name = *pMeterName;

  if (type == ALTER_TABLE_ADD_COLUMN || type == ALTER_TABLE_TAGS_ADD) {
    pAlterTable->pAddColumns = pCols;
    assert(pVals == NULL);
  } else {
    /* ALTER_TABLE_TAGS_CHG, ALTER_TABLE_TAGS_SET, ALTER_TABLE_TAGS_DROP,
     * ALTER_TABLE_DROP_COLUMN */
    pAlterTable->varList = pVals;
    assert(pCols == NULL);
  }

  return pAlterTable;
}