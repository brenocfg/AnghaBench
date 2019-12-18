#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* int16_t ;
struct TYPE_7__ {char* pLast; TYPE_1__* path; } ;
struct TYPE_8__ {TYPE_2__ parser; } ;
struct TYPE_6__ {char* pos; size_t len; } ;
typedef  TYPE_2__ HttpParser ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int HTTP_MAX_URL ; 
 int /*<<< orphan*/  HTTP_UNSUPPORT_URL ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpToLowerUrl (char*) ; 
 char* strchr (char*,char) ; 

bool httpParseURL(HttpContext* pContext) {
  HttpParser* pParser = &pContext->parser;
  char* pSeek;
  char* pEnd = strchr(pParser->pLast, ' ');
  if (*pParser->pLast != '/') {
    httpSendErrorResp(pContext, HTTP_UNSUPPORT_URL);
    return false;
  }
  pParser->pLast++;

  for (int i = 0; i < HTTP_MAX_URL; i++) {
    pSeek = strchr(pParser->pLast, '/');
    if (pSeek == NULL) {
      break;
    }
    pParser->path[i].pos = pParser->pLast;
    if (pSeek <= pEnd) {
      pParser->path[i].len = (int16_t)(pSeek - pParser->pLast);
      pParser->path[i].pos[pParser->path[i].len] = 0;
      httpToLowerUrl(pParser->path[i].pos);
      pParser->pLast = pSeek + 1;
    } else {
      pParser->path[i].len = (int16_t)(pEnd - pParser->pLast);
      pParser->path[i].pos[pParser->path[i].len] = 0;
      httpToLowerUrl(pParser->path[i].pos);
      pParser->pLast = pEnd + 1;
      break;
    }
  }
  pParser->pLast = pEnd + 1;

  if (pParser->path[0].len == 0) {
    httpSendErrorResp(pContext, HTTP_UNSUPPORT_URL);
    return false;
  }

  return true;
}