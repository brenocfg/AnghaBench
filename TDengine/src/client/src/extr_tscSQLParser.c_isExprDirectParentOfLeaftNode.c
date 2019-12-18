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
struct TYPE_3__ {int /*<<< orphan*/ * pRight; int /*<<< orphan*/ * pLeft; } ;
typedef  TYPE_1__ tSQLExpr ;

/* Variables and functions */
 scalar_t__ isExprLeafNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool isExprDirectParentOfLeaftNode(tSQLExpr* pExpr) {
  return (pExpr->pLeft != NULL && pExpr->pRight != NULL) &&
         (isExprLeafNode(pExpr->pLeft) && isExprLeafNode(pExpr->pRight));
}