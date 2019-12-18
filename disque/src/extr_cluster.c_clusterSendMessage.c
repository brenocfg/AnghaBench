#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sndbuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ clusterLink ;
struct TYPE_8__ {TYPE_1__* cluster; int /*<<< orphan*/  el; } ;
struct TYPE_6__ {int /*<<< orphan*/  stats_bus_messages_sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  clusterWriteHandler ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 

void clusterSendMessage(clusterLink *link, unsigned char *msg, size_t msglen) {
    if (sdslen(link->sndbuf) == 0 && msglen != 0)
        aeCreateFileEvent(server.el,link->fd,AE_WRITABLE,
                    clusterWriteHandler,link);

    link->sndbuf = sdscatlen(link->sndbuf, msg, msglen);
    server.cluster->stats_bus_messages_sent++;
}