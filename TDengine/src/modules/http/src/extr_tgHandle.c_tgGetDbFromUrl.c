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
struct TYPE_7__ {TYPE_1__* path; } ;
struct TYPE_8__ {TYPE_2__ parser; } ;
struct TYPE_6__ {scalar_t__ len; char* pos; } ;
typedef  TYPE_2__ HttpParser ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_TG_DB_NOT_INPUT ; 
 int /*<<< orphan*/  HTTP_TG_DB_TOO_LONG ; 
 size_t TG_DB_URL_POS ; 
 scalar_t__ TSDB_DB_NAME_LEN ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_3__*,int /*<<< orphan*/ ) ; 

char *tgGetDbFromUrl(HttpContext *pContext) {
  HttpParser *pParser = &pContext->parser;
  if (pParser->path[TG_DB_URL_POS].len <= 0) {
    httpSendErrorResp(pContext, HTTP_TG_DB_NOT_INPUT);
    return NULL;
  }

  if (pParser->path[TG_DB_URL_POS].len >= TSDB_DB_NAME_LEN) {
    httpSendErrorResp(pContext, HTTP_TG_DB_TOO_LONG);
    return NULL;
  }

  return pParser->path[TG_DB_URL_POS].pos;
}