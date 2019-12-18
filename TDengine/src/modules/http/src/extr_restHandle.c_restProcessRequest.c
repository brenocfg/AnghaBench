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
struct HttpContext {int /*<<< orphan*/  pass; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_PARSE_URL_ERROR ; 
 int /*<<< orphan*/  HTTP_PARSE_USR_ERROR ; 
 int /*<<< orphan*/  REST_ACTION_URL_POS ; 
 int /*<<< orphan*/  REST_TIMESTAMP_FMT_LOCAL_STRING ; 
 int /*<<< orphan*/  REST_TIMESTAMP_FMT_TIMESTAMP ; 
 int /*<<< orphan*/  REST_TIMESTAMP_FMT_UTC_STRING ; 
 int /*<<< orphan*/  httpSendErrorResp (struct HttpContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ httpUrlMatch (struct HttpContext*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  restGetPassFromUrl (struct HttpContext*) ; 
 int /*<<< orphan*/  restGetUserFromUrl (struct HttpContext*) ; 
 int restProcessLoginRequest (struct HttpContext*) ; 
 int restProcessSqlRequest (struct HttpContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

bool restProcessRequest(struct HttpContext* pContext) {
  if (httpUrlMatch(pContext, REST_ACTION_URL_POS, "login")) {
    restGetUserFromUrl(pContext);
    restGetPassFromUrl(pContext);
  }

  if (strlen(pContext->user) == 0 || strlen(pContext->pass) == 0) {
    httpSendErrorResp(pContext, HTTP_PARSE_USR_ERROR);
    return false;
  }

  if (httpUrlMatch(pContext, REST_ACTION_URL_POS, "sql")) {
    return restProcessSqlRequest(pContext, REST_TIMESTAMP_FMT_LOCAL_STRING);
  } else if (httpUrlMatch(pContext, REST_ACTION_URL_POS, "sqlt")) {
    return restProcessSqlRequest(pContext, REST_TIMESTAMP_FMT_TIMESTAMP);
  } else if (httpUrlMatch(pContext, REST_ACTION_URL_POS, "sqlutc")) {
    return restProcessSqlRequest(pContext, REST_TIMESTAMP_FMT_UTC_STRING);
  } else if (httpUrlMatch(pContext, REST_ACTION_URL_POS, "login")) {
    return restProcessLoginRequest(pContext);
  } else {
  }

  httpSendErrorResp(pContext, HTTP_PARSE_URL_ERROR);
  return false;
}