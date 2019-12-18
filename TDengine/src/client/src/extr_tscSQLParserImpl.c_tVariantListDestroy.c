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
struct TYPE_4__ {size_t nExpr; struct TYPE_4__* a; int /*<<< orphan*/  pVar; } ;
typedef  TYPE_1__ tVariantList ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  tVariantDestroy (int /*<<< orphan*/ *) ; 

void tVariantListDestroy(tVariantList *pList) {
  if (pList == NULL) return;

  for (int32_t i = 0; i < pList->nExpr; ++i) {
    tVariantDestroy(&pList->a[i].pVar);
  }

  free(pList->a);
  free(pList);
}