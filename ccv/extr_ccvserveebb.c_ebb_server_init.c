#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ev_loop {int dummy; } ;
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {char* port; int fd; int /*<<< orphan*/ * data; int /*<<< orphan*/ * new_connection; scalar_t__ secure; TYPE_2__ connection_watcher; scalar_t__ listening; struct ev_loop* loop; } ;
typedef  TYPE_1__ ebb_server ;

/* Variables and functions */
 int /*<<< orphan*/  ev_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_connection ; 

void 
ebb_server_init(ebb_server *server, struct ev_loop *loop)
{
  server->loop = loop;
  server->listening = 0;
  server->port[0] = '\0';
  server->fd = -1;
  server->connection_watcher.data = server;
  ev_init (&server->connection_watcher, on_connection);
  server->secure = 0;

  server->new_connection = NULL;
  server->data = NULL;
}