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
struct TYPE_4__ {TYPE_2__* pRight; int /*<<< orphan*/  nSQLBinaryOptr; TYPE_2__* pLeft; } ;
typedef  TYPE_1__ tSQLBinaryExpr ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  nodeType; } ;

/* Variables and functions */
 scalar_t__ tSQLBinaryExprToStringImpl (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 char* tSQLOptrToString (int /*<<< orphan*/ ,char*) ; 

void tSQLBinaryExprToString(tSQLBinaryExpr *pExpr, char *dst, int32_t *len) {
  if (pExpr == NULL) {
    *dst = 0;
    *len = 0;
  }

  int32_t lhs = tSQLBinaryExprToStringImpl(pExpr->pLeft, dst, pExpr->pLeft->nodeType);
  dst += lhs;
  *len = lhs;

  char *start = tSQLOptrToString(pExpr->nSQLBinaryOptr, dst);
  *len += (start - dst);

  *len += tSQLBinaryExprToStringImpl(pExpr->pRight, start, pExpr->pRight->nodeType);
}