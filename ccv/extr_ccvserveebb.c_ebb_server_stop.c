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
struct TYPE_3__ {char* port; scalar_t__ listening; int /*<<< orphan*/  fd; int /*<<< orphan*/  connection_watcher; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ ebb_server ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
ebb_server_stop(ebb_server *server)
{
  if(server->listening) {
    ev_io_stop(server->loop, &server->connection_watcher);
    close(server->fd);
    server->port[0] = '\0';
    server->listening = 0;
  }
}