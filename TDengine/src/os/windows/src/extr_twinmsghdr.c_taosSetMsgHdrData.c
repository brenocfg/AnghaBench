#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t dwBufferCount; TYPE_1__* lpBuffers; } ;
typedef  TYPE_2__ WSAMSG ;
struct TYPE_3__ {char* buf; int len; } ;

/* Variables and functions */

void taosSetMsgHdrData(void *hdr, char *data, int dataLen) {
    WSAMSG *msgHdr = (WSAMSG *)hdr;
    msgHdr->lpBuffers[msgHdr->dwBufferCount].buf = data;
    msgHdr->lpBuffers[msgHdr->dwBufferCount].len = dataLen;
    msgHdr->dwBufferCount++;
}