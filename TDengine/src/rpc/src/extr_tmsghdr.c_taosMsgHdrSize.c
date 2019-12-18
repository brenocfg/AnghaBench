#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msghdr {scalar_t__ msg_iovlen; } ;

/* Variables and functions */

int taosMsgHdrSize(void *hdr) {
  struct msghdr *msgHdr = (struct msghdr *)hdr;
  return (int)msgHdr->msg_iovlen;
}