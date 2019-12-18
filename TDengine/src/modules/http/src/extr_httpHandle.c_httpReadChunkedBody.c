#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  HttpParser ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 int HTTP_CHECK_BODY_CONTINUE ; 
 int HTTP_CHECK_BODY_ERROR ; 
 int HTTP_CHECK_BODY_SUCCESS ; 
 int /*<<< orphan*/  httpError (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int httpParseChunkedBody (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  httpReadDataImp (TYPE_1__*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool httpReadChunkedBody(HttpContext* pContext, HttpParser* pParser) {
  bool parsedOk = httpParseChunkedBody(pContext, pParser, true);
  if (parsedOk) {
    httpParseChunkedBody(pContext, pParser, false);
    return HTTP_CHECK_BODY_SUCCESS;
  } else {
    httpTrace("context:%p, fd:%d, ip:%s, chunked body not finished, continue read", pContext, pContext->fd,
              pContext->ipstr);
    if (!httpReadDataImp(pContext)) {
      httpError("context:%p, fd:%d, ip:%s, read chunked request error", pContext, pContext->fd, pContext->ipstr);
      return HTTP_CHECK_BODY_ERROR;
    } else {
      return HTTP_CHECK_BODY_CONTINUE;
    }
  }
}