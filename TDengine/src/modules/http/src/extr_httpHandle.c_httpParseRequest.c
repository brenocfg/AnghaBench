#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int pos; } ;
struct TYPE_15__ {int pCur; int pLast; TYPE_2__ data; int /*<<< orphan*/  buffer; int /*<<< orphan*/  bufsize; } ;
struct TYPE_16__ {int parsed; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_3__ parser; TYPE_1__* pThread; } ;
struct TYPE_13__ {int /*<<< orphan*/  numOfFds; int /*<<< orphan*/  label; } ;
typedef  TYPE_3__ HttpParser ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpGetDecodeMethod (TYPE_4__*) ; 
 int /*<<< orphan*/  httpGetHttpMethod (TYPE_4__*) ; 
 int /*<<< orphan*/  httpGetNextLine (TYPE_4__*) ; 
 int /*<<< orphan*/  httpParseHead (TYPE_4__*) ; 
 int /*<<< orphan*/  httpParseHttpVersion (TYPE_4__*) ; 
 int /*<<< orphan*/  httpParseURL (TYPE_4__*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

bool httpParseRequest(HttpContext* pContext) {
  HttpParser *pParser = &pContext->parser;
  if (pContext->parsed) {
    return true;
  }

  httpTrace("context:%p, fd:%d, ip:%s, thread:%s, numOfFds:%d, read size:%d, raw data:\n%s",
           pContext, pContext->fd, pContext->ipstr, pContext->pThread->label, pContext->pThread->numOfFds,
           pContext->parser.bufsize, pContext->parser.buffer);

  if (!httpGetHttpMethod(pContext)) {
    return false;
  }

  if (!httpParseURL(pContext)) {
    return false;
  }

  if (!httpParseHttpVersion(pContext)) {
    return false;
  }

  if (!httpGetDecodeMethod(pContext)) {
    return false;
  }

  do {
    if (!httpGetNextLine(pContext)) {
      return false;
    }

    // Empty line, end of the HTTP HEAD
    if (pParser->pCur - pParser->pLast == 1) {
      pParser->data.pos = ++pParser->pCur;
      break;
    }

    if (!httpParseHead(pContext)) {
      return false;
    }

    pParser->pLast = ++pParser->pCur;
  } while (1);

  httpTrace("context:%p, fd:%d, ip:%s, parse http head ok", pContext, pContext->fd, pContext->ipstr);

  pContext->parsed = true;
  return true;
}