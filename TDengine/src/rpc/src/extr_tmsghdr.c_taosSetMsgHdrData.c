#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msghdr {size_t msg_iovlen; TYPE_1__* msg_iov; } ;
struct TYPE_2__ {char* iov_base; size_t iov_len; } ;

/* Variables and functions */

void taosSetMsgHdrData(void *hdr, char *data, int dataLen) {
  struct msghdr *msgHdr = (struct msghdr *)hdr;
  msgHdr->msg_iov[msgHdr->msg_iovlen].iov_base = data;
  msgHdr->msg_iov[msgHdr->msg_iovlen].iov_len = (size_t)dataLen;
  msgHdr->msg_iovlen++;
}