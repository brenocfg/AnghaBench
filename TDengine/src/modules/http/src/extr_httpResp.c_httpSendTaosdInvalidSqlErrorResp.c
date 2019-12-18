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
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_INVALID_SQL ; 
 int /*<<< orphan*/  httpSendErrorRespImp (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,char*) ; 
 int sprintf (char*,char*,char*) ; 

void httpSendTaosdInvalidSqlErrorResp(HttpContext *pContext, char* errMsg) {
  int httpCode = 400;
  char temp[512] = {0};
  int len = sprintf(temp, "invalid SQL: %s", errMsg);

  for (int i = 0; i < len; ++i) {
    if (temp[i] == '\"') {
      temp[i] = '\'';
    } else if (temp[i] == '\n') {
        temp[i] = ' ';
    } else {}
  }

  httpSendErrorRespImp(pContext, httpCode, "Bad Request", TSDB_CODE_INVALID_SQL, temp);
}