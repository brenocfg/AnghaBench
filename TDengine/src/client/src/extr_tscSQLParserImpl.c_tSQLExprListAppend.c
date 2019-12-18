#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nAlloc; int nExpr; struct tSQLExprItem* a; } ;
typedef  TYPE_1__ tSQLExprList ;
typedef  int /*<<< orphan*/  tSQLExpr ;
struct tSQLExprItem {scalar_t__* aliasName; int /*<<< orphan*/ * pNode; } ;
struct TYPE_8__ {int n; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ SSQLToken ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* calloc (int,int) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memset (struct tSQLExprItem*,int /*<<< orphan*/ ,int) ; 
 struct tSQLExprItem* realloc (struct tSQLExprItem*,int) ; 
 int /*<<< orphan*/  strdequote (scalar_t__*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

tSQLExprList *tSQLExprListAppend(tSQLExprList *pList, tSQLExpr *pNode, SSQLToken *pToken) {
  if (pList == NULL) {
    pList = calloc(1, sizeof(tSQLExprList));
  }

  if (pList->nAlloc <= pList->nExpr) {  //
    pList->nAlloc = (pList->nAlloc << 1) + 4;
    pList->a = realloc(pList->a, pList->nAlloc * sizeof(pList->a[0]));
    if (pList->a == 0) {
      pList->nExpr = pList->nAlloc = 0;
      return pList;
    }
  }
  assert(pList->a != 0);

  if (pNode || pToken) {
    struct tSQLExprItem *pItem = &pList->a[pList->nExpr++];
    memset(pItem, 0, sizeof(*pItem));
    pItem->pNode = pNode;
    if (pToken) {  // set the as clause
      pItem->aliasName = malloc(pToken->n + 1);
      strncpy(pItem->aliasName, pToken->z, pToken->n);
      pItem->aliasName[pToken->n] = 0;

      strdequote(pItem->aliasName);
    }
  }
  return pList;
}