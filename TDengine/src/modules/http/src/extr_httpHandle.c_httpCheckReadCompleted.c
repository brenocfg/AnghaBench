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
struct TYPE_5__ {scalar_t__ httpChunked; int /*<<< orphan*/  parser; } ;
typedef  int /*<<< orphan*/  HttpParser ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 int HTTP_CHECK_BODY_SUCCESS ; 
 scalar_t__ HTTP_UNCUNKED ; 
 int httpReadChunkedBody (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int httpReadUnChunkedBody (TYPE_1__*,int /*<<< orphan*/ *) ; 

int httpCheckReadCompleted(HttpContext* pContext) {
  HttpParser *pParser = &pContext->parser;
  if (pContext->httpChunked == HTTP_UNCUNKED) {
    int ret = httpReadUnChunkedBody(pContext, pParser);
    if (ret != HTTP_CHECK_BODY_SUCCESS) {
      return ret;
    }
  } else {
    int ret = httpReadChunkedBody(pContext, pParser);
    if (ret != HTTP_CHECK_BODY_SUCCESS) {
      return ret;
    }
  }

  return HTTP_CHECK_BODY_SUCCESS;
}