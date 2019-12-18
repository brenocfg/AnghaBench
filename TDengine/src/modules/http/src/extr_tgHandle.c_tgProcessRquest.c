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
 int /*<<< orphan*/  HTTP_PARSE_USR_ERROR ; 
 int /*<<< orphan*/  httpSendErrorResp (struct HttpContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 char* tgGetDbFromUrl (struct HttpContext*) ; 
 int tgProcessQueryRequest (struct HttpContext*,char*) ; 

bool tgProcessRquest(struct HttpContext *pContext) {
  if (strlen(pContext->user) == 0 || strlen(pContext->pass) == 0) {
    httpSendErrorResp(pContext, HTTP_PARSE_USR_ERROR);
    return false;
  }

  char *db = tgGetDbFromUrl(pContext);
  if (db == NULL) {
    return false;
  }

  return tgProcessQueryRequest(pContext, db);
}