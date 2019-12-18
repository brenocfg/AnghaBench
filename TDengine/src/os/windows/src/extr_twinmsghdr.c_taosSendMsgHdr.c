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
struct TYPE_3__ {scalar_t__ dwBufferCount; } ;
typedef  TYPE_1__ WSAMSG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WSASendMsg (int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void taosSendMsgHdr(void *hdr, int fd) {
    WSAMSG *msgHdr = (WSAMSG *)hdr;
    DWORD len;

    WSASendMsg(fd, msgHdr, 0, &len, 0, 0);
    msgHdr->dwBufferCount = 0;
}