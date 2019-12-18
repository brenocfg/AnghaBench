#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; int /*<<< orphan*/  pass; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 int TSDB_PASSWORD_LEN ; 
 int TSDB_USER_LEN ; 
 scalar_t__ base64_decode (char*,int,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  httpError (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,size_t) ; 
 char* strstr (char*,char*) ; 

bool httpParseBasicAuthToken(HttpContext *pContext, char *token, int len) {
  token[len] = '\0';
  int   outlen = 0;
  char *base64 = (char *)base64_decode(token, len, &outlen);
  if (base64 == NULL || outlen == 0) {
    httpError("context:%p, fd:%d, ip:%s, basic token:%s parsed error", pContext, pContext->fd, pContext->ipstr, token);
    return false;
  }

  char *user = strstr(base64, ":");
  if (user == NULL) {
    httpError("context:%p, fd:%d, ip:%s, basic token:%s invalid format", pContext, pContext->fd, pContext->ipstr,
              token);
    free(base64);
    return false;
  }

  int user_len = (int)(user - base64);
  if (user_len < 1 || user_len >= TSDB_USER_LEN) {
    httpError("context:%p, fd:%d, ip:%s, basic token:%s parse user error", pContext, pContext->fd, pContext->ipstr,
              token);
    free(base64);
    return false;
  }
  strncpy(pContext->user, base64, (size_t)user_len);

  char *password = user + 1;
  int   pass_len = (int)((base64 + outlen) - password);
  if (pass_len < 1 || pass_len >= TSDB_PASSWORD_LEN) {
    httpError("context:%p, fd:%d, ip:%s, basic token:%s parse password error", pContext, pContext->fd, pContext->ipstr,
              token);
    free(base64);
    return false;
  }
  strncpy(pContext->pass, password, (size_t)pass_len);

  free(base64);
  httpTrace("context:%p, fd:%d, ip:%s, basic token parsed success, user:%s", pContext, pContext->fd, pContext->ipstr,
            pContext->user);
  return true;
}