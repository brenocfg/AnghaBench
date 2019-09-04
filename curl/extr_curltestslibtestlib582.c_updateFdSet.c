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
struct Sockets {int count; scalar_t__* sockets; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void updateFdSet(struct Sockets* sockets, fd_set* fdset,
                        curl_socket_t *maxFd)
{
  int i;
  for(i = 0; i < sockets->count; ++i) {
    FD_SET(sockets->sockets[i], fdset);
    if(*maxFd < sockets->sockets[i] + 1) {
      *maxFd = sockets->sockets[i] + 1;
    }
  }
}