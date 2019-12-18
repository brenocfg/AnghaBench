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
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  pVal; TYPE_1__* pSchema; int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ tSQLSyntaxNode ;
typedef  int int32_t ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 scalar_t__ TSQL_NODE_COL ; 
 scalar_t__ TSQL_NODE_EXPR ; 
 int sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  tSQLBinaryExprToString (int /*<<< orphan*/ ,char*,int*) ; 
 int tVariantToString (int /*<<< orphan*/ ,char*) ; 

int32_t tSQLBinaryExprToStringImpl(tSQLSyntaxNode *pNode, char *dst, uint8_t type) {
  int32_t len = 0;
  if (type == TSQL_NODE_EXPR) {
    *dst = '(';
    tSQLBinaryExprToString(pNode->pExpr, dst + 1, &len);
    len += 2;
    *(dst + len - 1) = ')';
  } else if (type == TSQL_NODE_COL) {
    len = sprintf(dst, "%s", pNode->pSchema->name);
  } else {
    len = tVariantToString(pNode->pVal, dst);
  }
  return len;
}