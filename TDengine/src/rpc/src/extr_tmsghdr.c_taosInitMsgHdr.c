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
struct sockaddr_in {int dummy; } ;
struct msghdr {int msg_namelen; struct msghdr* msg_iov; struct sockaddr_in* msg_name; } ;
struct iovec {int msg_namelen; struct iovec* msg_iov; struct sockaddr_in* msg_name; } ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,size_t) ; 

void taosInitMsgHdr(void **hdr, void *dest, int maxPkts) {
  struct msghdr *msgHdr = (struct msghdr *)malloc(sizeof(struct msghdr));
  memset(msgHdr, 0, sizeof(struct msghdr));
  *hdr = msgHdr;
  struct sockaddr_in *destAdd = (struct sockaddr_in *)dest;

  msgHdr->msg_name = destAdd;
  msgHdr->msg_namelen = sizeof(struct sockaddr_in);
  int size = (int)sizeof(struct iovec) * maxPkts;
  msgHdr->msg_iov = (struct iovec *)malloc((size_t)size);
  memset(msgHdr->msg_iov, 0, (size_t)size);
}