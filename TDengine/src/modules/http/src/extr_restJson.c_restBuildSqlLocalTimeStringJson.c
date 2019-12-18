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
typedef  int /*<<< orphan*/  HttpSqlCmd ;
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  REST_TIMESTAMP_FMT_LOCAL_STRING ; 
 int restBuildSqlJson (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

bool restBuildSqlLocalTimeStringJson(HttpContext *pContext, HttpSqlCmd *cmd, TAOS_RES *result, int numOfRows) {
  return restBuildSqlJson(pContext,cmd, result, numOfRows, REST_TIMESTAMP_FMT_LOCAL_STRING);
}