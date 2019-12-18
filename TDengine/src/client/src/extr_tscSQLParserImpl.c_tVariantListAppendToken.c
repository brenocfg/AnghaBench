#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  sortOrder; } ;
typedef  TYPE_1__ tVariantListItem ;
struct TYPE_12__ {int /*<<< orphan*/  nExpr; TYPE_1__* a; } ;
typedef  TYPE_2__ tVariantList ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ tVariant ;
typedef  int /*<<< orphan*/  SSQLToken ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  tVariantCreate (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tVariantListExpand (TYPE_2__*) ; 

tVariantList *tVariantListAppendToken(tVariantList *pList, SSQLToken *pAliasToken, uint8_t sortOrder) {
  if (pList == NULL) {
    pList = calloc(1, sizeof(tVariantList));
  }

  if (tVariantListExpand(pList) == NULL) {
    return pList;
  }

  if (pAliasToken) {
    tVariant t = {0};
    tVariantCreate(&t, pAliasToken);

    tVariantListItem *pItem = &pList->a[pList->nExpr++];
    memcpy(pItem, &t, sizeof(tVariant));
    pItem->sortOrder = sortOrder;
  }
  return pList;
}