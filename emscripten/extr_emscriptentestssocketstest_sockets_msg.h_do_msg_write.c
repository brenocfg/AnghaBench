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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_3__ {int length; int* buffer; } ;
typedef  TYPE_1__ msg_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int send (int,int*,int,int /*<<< orphan*/ ) ; 
 int sendto (int,int*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 

int do_msg_write(int sockfd, msg_t *msg, int offset, int length, struct sockaddr *addr, socklen_t addrlen) {
  int res;

  // send the message length first
  if (!offset) {
    if (addr) {
      res = sendto(sockfd, &msg->length, sizeof(int), 0, addr, addrlen);
    } else {
      res = send(sockfd, &msg->length, sizeof(int), 0);
    }
    if (res == -1) {
      assert(errno == EAGAIN);
      return res;
    }
    printf("do_msg_write: sending message header for %d bytes\n", msg->length);
    assert(res == sizeof(int));
  }

  // then the actual message
  int max = msg->length - offset;
  if (length && max > length) {
    max = length;
  }
  if (addr) {
    res = sendto(sockfd, msg->buffer + offset, max, 0, addr, addrlen);
  } else {
    res = send(sockfd, msg->buffer + offset, max, 0);
  }
  if (res == -1) {
    assert(errno == EAGAIN);
    return res;
  }

  printf("do_msg_write: wrote %d bytes %d\n", res, msg->length);

  return res;
}