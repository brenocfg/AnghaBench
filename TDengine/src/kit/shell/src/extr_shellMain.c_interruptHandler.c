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
 int /*<<< orphan*/  con ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * result ; 
 int /*<<< orphan*/  taos_stop_query (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscQueueAsyncFreeResult (int /*<<< orphan*/ *) ; 

void interruptHandler(int signum) {
#ifdef LINUX
  TAOS_RES* res = taos_use_result(con);
  taos_stop_query(res);
  if (res != NULL) {
    /*
     * we need to free result in async model, in order to avoid free
     * results while the master thread is waiting for server response.
     */
    tscQueueAsyncFreeResult(res);
  }
  result = NULL;
#else
  printf("\nReceive ctrl+c or other signal, quit shell.\n");
  exit(0);
#endif
}