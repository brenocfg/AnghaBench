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
struct TYPE_3__ {int listening; int fd; int /*<<< orphan*/  connection_watcher; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ ebb_server ;

/* Variables and functions */
 int /*<<< orphan*/  EBB_MAX_CONNECTIONS ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ev_io_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ listen (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  set_nonblock (int const) ; 

int 
ebb_server_listen_on_fd(ebb_server *server, const int fd)
{
  assert(server->listening == 0);

  if (listen(fd, EBB_MAX_CONNECTIONS) < 0) {
    perror("listen()");
    return -1;
  }
  
  set_nonblock(fd); /* XXX superfluous? */
  
  server->fd = fd;
  server->listening = 1;
  
  ev_io_set (&server->connection_watcher, server->fd, EV_READ);
  ev_io_start (server->loop, &server->connection_watcher);
  
  return server->fd;
}