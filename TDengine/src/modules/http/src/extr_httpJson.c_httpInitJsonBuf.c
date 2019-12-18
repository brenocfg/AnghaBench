#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct HttpContext {scalar_t__ acceptEncoding; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {struct HttpContext* pContext; int /*<<< orphan*/  lst; int /*<<< orphan*/  size; scalar_t__ total; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ JsonBuf ;

/* Variables and functions */
 scalar_t__ HTTP_COMPRESS_GZIP ; 
 int /*<<< orphan*/  JSON_BUFFER_SIZE ; 
 int /*<<< orphan*/  httpGzipCompressInit (struct HttpContext*) ; 
 int /*<<< orphan*/  httpTrace (char*,struct HttpContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void httpInitJsonBuf(JsonBuf* buf, struct HttpContext* pContext) {
  buf->lst = buf->buf;
  buf->total = 0;
  buf->size = JSON_BUFFER_SIZE;  // option setting
  buf->pContext = pContext;
  memset(buf->lst, 0, JSON_BUFFER_SIZE);

  if (pContext->acceptEncoding == HTTP_COMPRESS_GZIP) {
    httpGzipCompressInit(buf->pContext);
  }

  httpTrace("context:%p, fd:%d, ip:%s, json buffer initialized", buf->pContext, buf->pContext->fd, buf->pContext->ipstr);
}