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
typedef  unsigned int uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__ numOfAlloc; int /*<<< orphan*/ * pExprs; } ;
typedef  TYPE_1__ SSqlExprInfo ;
typedef  int /*<<< orphan*/  SSqlExpr ;

/* Variables and functions */
 unsigned int TSDB_MAX_COLUMNS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void _exprCheckSpace(SSqlExprInfo* pExprInfo, int32_t size) {
  if (size > pExprInfo->numOfAlloc) {
    uint32_t oldSize = pExprInfo->numOfAlloc;

    uint32_t newSize = (oldSize <= 0) ? 8 : (oldSize << 1U);
    while (newSize < size) {
      newSize = (newSize << 1U);
    }

    if (newSize > TSDB_MAX_COLUMNS) {
      newSize = TSDB_MAX_COLUMNS;
    }

    int32_t inc = newSize - oldSize;

    pExprInfo->pExprs = realloc(pExprInfo->pExprs, newSize * sizeof(SSqlExpr));
    memset(&pExprInfo->pExprs[oldSize], 0, inc * sizeof(SSqlExpr));

    pExprInfo->numOfAlloc = newSize;
  }
}