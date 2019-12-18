#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TAOS_RES ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscError (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tscSaveSlowQueryFp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tscSlowQueryConn ; 
 int tscSlowQueryConnInitialized ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ *,int) ; 

void tscInitConnCb(void *param, TAOS_RES *result, int code) {
  char *sql = param;
  if (code < 0) {
    tscError("taos:%p, slow query connect failed, code:%d", tscSlowQueryConn, code);
    taos_close(tscSlowQueryConn);
    tscSlowQueryConn = NULL;
    tscSlowQueryConnInitialized = false;
    free(sql);
  } else {
    tscTrace("taos:%p, slow query connect success, code:%d", tscSlowQueryConn, code);
    tscSlowQueryConnInitialized = true;
    tscSaveSlowQueryFp(sql, NULL);
  }
}