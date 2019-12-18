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
struct Sockets {int max_count; int count; scalar_t__* sockets; } ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*) ; 
 scalar_t__* malloc (int) ; 
 scalar_t__* realloc (scalar_t__*,int) ; 
 int /*<<< orphan*/  removeFd (struct Sockets*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void addFd(struct Sockets* sockets, curl_socket_t fd, const char *what)
{
  /**
   * To ensure we only have each file descriptor once, we remove it then add
   * it again.
   */
  fprintf(stderr, "Add socket fd %d for %s\n", (int) fd, what);
  removeFd(sockets, fd, 0);
  /*
   * Allocate array storage when required.
   */
  if(!sockets->sockets) {
    sockets->sockets = malloc(sizeof(curl_socket_t) * 20U);
    if(!sockets->sockets)
      return;
    sockets->max_count = 20;
  }
  else if(sockets->count + 1 > sockets->max_count) {
    curl_socket_t *oldptr = sockets->sockets;
    sockets->sockets = realloc(oldptr, sizeof(curl_socket_t) *
                               (sockets->max_count + 20));
    if(!sockets->sockets) {
      /* cleanup in test_cleanup */
      sockets->sockets = oldptr;
      return;
    }
    sockets->max_count += 20;
  }
  /*
   * Add file descriptor to array.
   */
  sockets->sockets[sockets->count] = fd;
  ++sockets->count;
}