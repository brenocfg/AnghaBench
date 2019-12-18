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
struct TYPE_2__ {struct TYPE_2__* signature; } ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ STscObj ;

/* Variables and functions */
 int TSDB_CODE_DISCONNECTED ; 
 int globalCode ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int taos_query (int /*<<< orphan*/ *,char*) ; 

int taos_select_db(TAOS *taos, const char *db) {
  char sql[64];

  STscObj *pObj = (STscObj *)taos;
  if (pObj == NULL || pObj->signature != pObj) {
    globalCode = TSDB_CODE_DISCONNECTED;
    return TSDB_CODE_DISCONNECTED;
  }

  sprintf(sql, "use %s", db);

  return taos_query(taos, sql);
}