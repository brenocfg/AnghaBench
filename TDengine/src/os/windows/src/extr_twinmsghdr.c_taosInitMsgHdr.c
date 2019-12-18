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
struct sockaddr_in {int dummy; } ;
struct TYPE_4__ {int namelen; scalar_t__ dwBufferCount; struct TYPE_4__* lpBuffers; scalar_t__ name; } ;
typedef  TYPE_1__ WSAMSG ;
typedef  int /*<<< orphan*/  WSABUF ;
typedef  TYPE_1__* LPWSABUF ;
typedef  scalar_t__ LPSOCKADDR ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void taosInitMsgHdr(void **hdr, void *dest, int maxPkts) {
    WSAMSG *msgHdr = (WSAMSG *)malloc(sizeof(WSAMSG));
    memset(msgHdr, 0, sizeof(WSAMSG));
    *hdr = msgHdr;

    // see ws2def.h
    // the size of LPSOCKADDR and sockaddr_in * is same, so it's safe
    msgHdr->name = (LPSOCKADDR)dest;
    msgHdr->namelen = sizeof(struct sockaddr_in);
    int size = sizeof(WSABUF) * maxPkts;
    msgHdr->lpBuffers = (LPWSABUF)malloc(size);
    memset(msgHdr->lpBuffers, 0, size);
    msgHdr->dwBufferCount = 0;
}