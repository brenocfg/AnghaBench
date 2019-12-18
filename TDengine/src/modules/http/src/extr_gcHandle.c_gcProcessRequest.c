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
 int /*<<< orphan*/  GC_ACTION_URL_POS ; 
 int /*<<< orphan*/  HTTP_PARSE_USR_ERROR ; 
 int /*<<< orphan*/  gcGetPassFromUrl (struct HttpContext*) ; 
 int /*<<< orphan*/  gcGetUserFromUrl (struct HttpContext*) ; 
 int gcProcessHeartbeatRequest (struct HttpContext*) ; 
 int gcProcessLoginRequest (struct HttpContext*) ; 
 int gcProcessQueryRequest (struct HttpContext*) ; 
 int /*<<< orphan*/  httpSendErrorResp (struct HttpContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ httpUrlMatch (struct HttpContext*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

bool gcProcessRequest(struct HttpContext* pContext) {
  if (httpUrlMatch(pContext, GC_ACTION_URL_POS, "login")) {
    gcGetUserFromUrl(pContext);
    gcGetPassFromUrl(pContext);
  }

  if (strlen(pContext->user) == 0 || strlen(pContext->pass) == 0) {
    httpSendErrorResp(pContext, HTTP_PARSE_USR_ERROR);
    return false;
  }

  if (httpUrlMatch(pContext, GC_ACTION_URL_POS, "query")) {
    return gcProcessQueryRequest(pContext);
  } else if (httpUrlMatch(pContext, GC_ACTION_URL_POS, "heartbeat")) {
    return gcProcessHeartbeatRequest(pContext);
  } else if (httpUrlMatch(pContext, GC_ACTION_URL_POS, "login")) {
    return gcProcessLoginRequest(pContext);
  } else {
    return gcProcessHeartbeatRequest(pContext);
  }
}