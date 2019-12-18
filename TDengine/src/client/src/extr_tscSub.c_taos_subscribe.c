#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {char const* name; int mseconds; scalar_t__ lastKey; int numOfFields; int /*<<< orphan*/  result; int /*<<< orphan*/  fields; int /*<<< orphan*/ * taos; struct TYPE_6__* signature; } ;
typedef  TYPE_1__ TAOS_SUB ;
typedef  int /*<<< orphan*/  TAOS_FIELD ;
typedef  TYPE_1__ SSub ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char const*,char const*) ; 
 scalar_t__ taosGetTimestampMs () ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_connect (char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_errstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_fetch_fields (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_init () ; 
 int taos_num_fields (int /*<<< orphan*/ ) ; 
 int taos_query (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  taos_use_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 
 int /*<<< orphan*/  tscError (char*,char const*) ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ ) ; 

TAOS_SUB *taos_subscribe(const char *host, const char *user, const char *pass, const char *db, const char *name, int64_t time, int mseconds) {
  SSub *pSub;

  pSub = (SSub *)malloc(sizeof(SSub));
  if (pSub == NULL) return NULL;
  memset(pSub, 0, sizeof(SSub));

  pSub->signature = pSub;
  strcpy(pSub->name, name);
  pSub->mseconds = mseconds;
  pSub->lastKey = time;
  if (pSub->lastKey == 0) {
    pSub->lastKey = taosGetTimestampMs();
  }

  taos_init();
  pSub->taos = taos_connect(host, user, pass, NULL, 0);
  if (pSub->taos == NULL) {
    tfree(pSub);
  } else {
    char qstr[128];
    sprintf(qstr, "use %s", db);
    int res = taos_query(pSub->taos, qstr);
    if (res != 0) {
      tscError("failed to open DB:%s", db);
      taos_close(pSub->taos);
      tfree(pSub);
    } else {
      sprintf(qstr, "select * from %s where _c0 > now+1000d", pSub->name);
      if (taos_query(pSub->taos, qstr)) {
        tscTrace("failed to select, reason:%s", taos_errstr(pSub->taos));
        taos_close(pSub->taos);
        tfree(pSub);
        return NULL;
      }
      pSub->result = taos_use_result(pSub->taos);
      pSub->numOfFields = taos_num_fields(pSub->result);
      memcpy(pSub->fields, taos_fetch_fields(pSub->result), sizeof(TAOS_FIELD) * pSub->numOfFields);
    }
  }

  return pSub;
}