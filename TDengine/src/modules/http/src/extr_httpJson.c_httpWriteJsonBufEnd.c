#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fd; int /*<<< orphan*/  ipstr; } ;
struct TYPE_6__ {TYPE_4__* pContext; } ;
typedef  TYPE_1__ JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpWriteBufNoTrace (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  httpWriteJsonBufBody (TYPE_1__*,int) ; 

void httpWriteJsonBufEnd(JsonBuf* buf) {
  if (buf->pContext->fd <= 0) {
    httpTrace("context:%p, fd:%d, ip:%s, json buf fd is 0", buf->pContext, buf->pContext->fd, buf->pContext->ipstr);
    buf->pContext->fd = -1;
  }

  httpWriteJsonBufBody(buf, true);
  httpWriteBufNoTrace(buf->pContext, "0\r\n\r\n", 5);  // end of chunked resp
}