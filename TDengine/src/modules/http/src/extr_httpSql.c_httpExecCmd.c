#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int reqType; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
#define  HTTP_REQTYPE_HEARTBEAT 132 
#define  HTTP_REQTYPE_LOGIN 131 
#define  HTTP_REQTYPE_MULTI_SQL 130 
#define  HTTP_REQTYPE_OTHERS 129 
#define  HTTP_REQTYPE_SINGLE_SQL 128 
 int /*<<< orphan*/  httpCloseContextByApp (TYPE_1__*) ; 
 int /*<<< orphan*/  httpProcessHeartBeatCmd (TYPE_1__*) ; 
 int /*<<< orphan*/  httpProcessLoginCmd (TYPE_1__*) ; 
 int /*<<< orphan*/  httpProcessMultiSqlCmd (TYPE_1__*) ; 
 int /*<<< orphan*/  httpProcessSingleSqlCmd (TYPE_1__*) ; 

void httpExecCmd(HttpContext *pContext) {
  switch (pContext->reqType) {
    case HTTP_REQTYPE_LOGIN:
      httpProcessLoginCmd(pContext);
      break;
    case HTTP_REQTYPE_SINGLE_SQL:
      httpProcessSingleSqlCmd(pContext);
      break;
    case HTTP_REQTYPE_MULTI_SQL:
      httpProcessMultiSqlCmd(pContext);
      break;
    case HTTP_REQTYPE_HEARTBEAT:
      httpProcessHeartBeatCmd(pContext);
      break;
    case HTTP_REQTYPE_OTHERS:
      httpCloseContextByApp(pContext);
      break;
    default:
      httpCloseContextByApp(pContext);
      break;
  }
}