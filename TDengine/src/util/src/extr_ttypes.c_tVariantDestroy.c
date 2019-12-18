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
struct TYPE_3__ {scalar_t__ nType; scalar_t__ nLen; int /*<<< orphan*/ * pz; } ;
typedef  TYPE_1__ tVariant ;

/* Variables and functions */
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void tVariantDestroy(tVariant *pVar) {
  if (pVar == NULL) return;

  if ((pVar->nType == TSDB_DATA_TYPE_BINARY || pVar->nType == TSDB_DATA_TYPE_NCHAR) && pVar->nLen > 0) {
    free(pVar->pz);
    pVar->pz = NULL;
    pVar->nLen = 0;
  }
}