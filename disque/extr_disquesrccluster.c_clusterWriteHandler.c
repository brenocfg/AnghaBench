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
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  sndbuf; } ;
typedef  TYPE_1__ clusterLink ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_5__ {int /*<<< orphan*/  el; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  handleLinkIOError (TYPE_1__*) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

void clusterWriteHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    clusterLink *link = (clusterLink*) privdata;
    ssize_t nwritten;
    UNUSED(el);
    UNUSED(mask);

    nwritten = write(fd, link->sndbuf, sdslen(link->sndbuf));
    if (nwritten <= 0) {
        serverLog(LL_DEBUG,"I/O error writing to node link: %s",
            strerror(errno));
        handleLinkIOError(link);
        return;
    }
    sdsrange(link->sndbuf,nwritten,-1);
    if (sdslen(link->sndbuf) == 0)
        aeDeleteFileEvent(server.el, link->fd, AE_WRITABLE);
}