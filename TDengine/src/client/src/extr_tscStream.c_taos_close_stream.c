#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* signature; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pSql; int /*<<< orphan*/  pTimer; } ;
typedef  int /*<<< orphan*/  TAOS_STREAM ;
typedef  TYPE_1__ SSqlStream ;
typedef  TYPE_2__ SSqlObj ;

/* Variables and functions */
 scalar_t__ atomic_exchange_ptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 
 int /*<<< orphan*/  tscFreeSqlObj (TYPE_2__*) ; 
 int /*<<< orphan*/  tscRemoveFromStreamList (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*,TYPE_1__*) ; 

void taos_close_stream(TAOS_STREAM *handle) {
  SSqlStream *pStream = (SSqlStream *)handle;

  SSqlObj *pSql = (SSqlObj *)atomic_exchange_ptr(&pStream->pSql, 0);
  if (pSql == NULL) {
    return;
  }

  /*
   * stream may be closed twice, 1. drop dst table, 2. kill stream
   * Here, we need a check before release memory
   */
  if (pSql->signature == pSql) {
    tscRemoveFromStreamList(pStream, pSql);

    taosTmrStopA(&(pStream->pTimer));
    tscFreeSqlObj(pSql);
    pStream->pSql = NULL;

    tscTrace("%p stream:%p is closed", pSql, pStream);
    tfree(pStream);
  }
}