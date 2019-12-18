#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nAlloc; int nField; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ tFieldList ;
struct TAOS_FIELD {int dummy; } ;
typedef  int /*<<< orphan*/  TAOS_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (struct TAOS_FIELD*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

tFieldList *tFieldListAppend(tFieldList *pList, TAOS_FIELD *pField) {
  if (pList == NULL) pList = calloc(1, sizeof(tFieldList));

  if (pList->nAlloc <= pList->nField) {  //
    pList->nAlloc = (pList->nAlloc << 1) + 4;
    pList->p = realloc(pList->p, pList->nAlloc * sizeof(pList->p[0]));
    if (pList->p == 0) {
      pList->nField = pList->nAlloc = 0;
      return pList;
    }
  }
  assert(pList->p != 0);

  if (pField) {
    struct TAOS_FIELD *pItem = (struct TAOS_FIELD *)&pList->p[pList->nField++];
    memcpy(pItem, pField, sizeof(TAOS_FIELD));
  }
  return pList;
}