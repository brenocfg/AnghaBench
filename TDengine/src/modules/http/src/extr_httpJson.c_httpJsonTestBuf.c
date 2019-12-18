#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lst; scalar_t__ buf; scalar_t__ size; } ;
typedef  TYPE_1__ JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  httpWriteJsonBufBody (TYPE_1__*,int) ; 

void httpJsonTestBuf(JsonBuf* buf, int safety) {
  if ((buf->lst - buf->buf + safety) < buf->size) return;
  // buf->slot = *buf->lst;
  httpWriteJsonBufBody(buf, false);
}