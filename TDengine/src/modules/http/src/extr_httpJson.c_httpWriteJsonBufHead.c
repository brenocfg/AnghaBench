#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; scalar_t__ acceptEncoding; size_t httpVersion; size_t httpKeepAlive; } ;
struct TYPE_4__ {TYPE_3__* pContext; } ;
typedef  TYPE_1__ JsonBuf ;

/* Variables and functions */
 scalar_t__ HTTP_COMPRESS_IDENTITY ; 
 size_t HTTP_RESPONSE_CHUNKED_COMPRESS ; 
 size_t HTTP_RESPONSE_CHUNKED_UN_COMPRESS ; 
 int /*<<< orphan*/ * httpKeepAliveStr ; 
 char** httpRespTemplate ; 
 int /*<<< orphan*/ * httpVersionStr ; 
 int /*<<< orphan*/  httpWriteBuf (TYPE_3__*,char const*,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void httpWriteJsonBufHead(JsonBuf* buf) {
  if (buf->pContext->fd <= 0) {
    buf->pContext->fd = -1;
  }

  char msg[1024] = {0};
  int  len = -1;

  if (buf->pContext->acceptEncoding == HTTP_COMPRESS_IDENTITY) {
    len = sprintf(msg, httpRespTemplate[HTTP_RESPONSE_CHUNKED_UN_COMPRESS], httpVersionStr[buf->pContext->httpVersion],
                  httpKeepAliveStr[buf->pContext->httpKeepAlive]);
  } else {
    len = sprintf(msg, httpRespTemplate[HTTP_RESPONSE_CHUNKED_COMPRESS], httpVersionStr[buf->pContext->httpVersion],
                  httpKeepAliveStr[buf->pContext->httpKeepAlive]);
  }

  httpWriteBuf(buf->pContext, (const char*)msg, len);
}