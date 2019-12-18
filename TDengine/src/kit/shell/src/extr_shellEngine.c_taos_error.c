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
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ *) ; 

void taos_error(TAOS *con) {
  fprintf(stderr, "\nDB error: %s\n", taos_errstr(con));

  /* free local resouce: allocated memory/metric-meta refcnt */
  TAOS_RES *pRes = taos_use_result(con);
  taos_free_result(pRes);
}