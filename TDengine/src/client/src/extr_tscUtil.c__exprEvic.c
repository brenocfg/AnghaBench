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
typedef  int int32_t ;
struct TYPE_3__ {int numOfExprs; int /*<<< orphan*/ * pExprs; } ;
typedef  TYPE_1__ SSqlExprInfo ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _exprEvic(SSqlExprInfo* pExprInfo, int32_t index) {
  if (index < pExprInfo->numOfExprs) {
    memmove(&pExprInfo->pExprs[index + 1], &pExprInfo->pExprs[index],
            sizeof(pExprInfo->pExprs[0]) * (pExprInfo->numOfExprs - index));
  }
}