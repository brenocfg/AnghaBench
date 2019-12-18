#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  table; int /*<<< orphan*/  stable; int /*<<< orphan*/  metric; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  int /*<<< orphan*/  JsonBuf ;
typedef  TYPE_1__ HttpSqlCmd ;
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  JsonObjStt ; 
 int /*<<< orphan*/  httpGetCmdsString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonPair (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  httpJsonToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * httpMallocJsonBuf (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void tgStartQueryJson(HttpContext *pContext, HttpSqlCmd *cmd, TAOS_RES *result) {
  JsonBuf *jsonBuf = httpMallocJsonBuf(pContext);
  if (jsonBuf == NULL) return;

  // object begin
  httpJsonItemToken(jsonBuf);
  httpJsonToken(jsonBuf, JsonObjStt);

  // data
  httpJsonItemToken(jsonBuf);
  httpJsonPair(jsonBuf, "metric", 6, httpGetCmdsString(pContext, cmd->stable),
               (int)strlen(httpGetCmdsString(pContext, cmd->metric)));

  httpJsonItemToken(jsonBuf);
  httpJsonPair(jsonBuf, "stable", 6, httpGetCmdsString(pContext, cmd->stable),
               (int)strlen(httpGetCmdsString(pContext, cmd->stable)));

  httpJsonItemToken(jsonBuf);
  httpJsonPair(jsonBuf, "table", 5, httpGetCmdsString(pContext, cmd->table),
               (int)strlen(httpGetCmdsString(pContext, cmd->table)));

  httpJsonItemToken(jsonBuf);
  httpJsonPair(jsonBuf, "timestamp", 9, httpGetCmdsString(pContext, cmd->timestamp),
               (int)strlen(httpGetCmdsString(pContext, cmd->timestamp)));  // hack way
}