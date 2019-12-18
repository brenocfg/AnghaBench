#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ mseconds; scalar_t__ stime; char* name; int /*<<< orphan*/  taos; int /*<<< orphan*/ * result; scalar_t__ lastKey; struct TYPE_2__* signature; } ;
typedef  int /*<<< orphan*/  TAOS_SUB ;
typedef  scalar_t__* TAOS_ROW ;
typedef  TYPE_1__ SSub ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*,scalar_t__) ; 
 void* taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosMsleep (int) ; 
 int /*<<< orphan*/  taos_errstr (int /*<<< orphan*/ ) ; 
 scalar_t__* taos_fetch_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ ) ; 

TAOS_ROW taos_consume(TAOS_SUB *tsub) {
  SSub *   pSub = (SSub *)tsub;
  TAOS_ROW row;
  char     qstr[256];

  if (pSub == NULL) return NULL;
  if (pSub->signature != pSub) return NULL;

  while (1) {
    if (pSub->result != NULL) {
      row = taos_fetch_row(pSub->result);
      if (row != NULL) {
        pSub->lastKey = *((uint64_t *)row[0]);
        return row;
      }

      taos_free_result(pSub->result);
      pSub->result = NULL;
      uint64_t etime = taosGetTimestampMs();
      int64_t  mseconds = pSub->mseconds - etime + pSub->stime;
      if (mseconds < 0) mseconds = 0;
      taosMsleep((int)mseconds);
    }

    pSub->stime = taosGetTimestampMs();

    sprintf(qstr, "select * from %s where _c0 > %lld order by _c0 asc", pSub->name, pSub->lastKey);
    if (taos_query(pSub->taos, qstr)) {
      tscTrace("failed to select, reason:%s", taos_errstr(pSub->taos));
      return NULL;
    }

    pSub->result = taos_use_result(pSub->taos);

    if (pSub->result == NULL) {
      tscTrace("failed to get result, reason:%s", taos_errstr(pSub->taos));
      return NULL;
    }
  }

  return NULL;
}