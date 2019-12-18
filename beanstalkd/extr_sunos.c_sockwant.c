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
struct TYPE_3__ {int added; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int /*<<< orphan*/  PORT_SOURCE_FD ; 
 int port_associate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int port_dissociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portfd ; 

int
sockwant(Socket *s, int rw)
{
    int events = 0;

    if (rw) {
        switch (rw) {
        case 'r':
            events |= POLLIN;
            break;
        case 'w':
            events |= POLLOUT;
            break;
        }
    }

    events |= POLLPRI;

    if (!s->added && !rw) {
        return 0;
    } else if (!s->added && rw) {
        s->added = 1;
        return port_associate(portfd, PORT_SOURCE_FD, s->fd, events, (void *)s);
    } else if (!rw) {
        return port_dissociate(portfd, PORT_SOURCE_FD, s->fd);
    } else {
        port_dissociate(portfd, PORT_SOURCE_FD, s->fd);
        return port_associate(portfd, PORT_SOURCE_FD, s->fd, events, (void *)s);
    }
}