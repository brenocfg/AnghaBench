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
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void removeFd(struct Sockets* sockets, curl_socket_t fd, int mention)
{
  int i;

  if(mention)
    fprintf(stderr, "Remove socket fd %d\n", (int) fd);

  for(i = 0; i < sockets->count; ++i) {
    if(sockets->sockets[i] == fd) {
      if(i < sockets->count - 1)
        memmove(&sockets->sockets[i], &sockets->sockets[i + 1],
              sizeof(curl_socket_t) * (sockets->count - (i + 1)));
      --sockets->count;
    }
  }
}