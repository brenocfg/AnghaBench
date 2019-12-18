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
 int /*<<< orphan*/  tscError (char*,int) ; 
 int /*<<< orphan*/  tscTrace (char*,int) ; 

void tscSaveSlowQueryFpCb(void *param, TAOS_RES *result, int code) {
  if (code < 0) {
    tscError("failed to save slow query, code:%d", code);
  } else {
    tscTrace("success to save slow query, code:%d", code);
  }
}