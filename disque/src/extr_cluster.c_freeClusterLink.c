#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fd; TYPE_1__* node; int /*<<< orphan*/  rcvbuf; int /*<<< orphan*/  sndbuf; } ;
typedef  TYPE_2__ clusterLink ;
struct TYPE_8__ {int /*<<< orphan*/  el; } ;
struct TYPE_6__ {int /*<<< orphan*/ * link; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void freeClusterLink(clusterLink *link) {
    if (link->fd != -1) {
        aeDeleteFileEvent(server.el, link->fd, AE_WRITABLE);
        aeDeleteFileEvent(server.el, link->fd, AE_READABLE);
    }
    sdsfree(link->sndbuf);
    sdsfree(link->rcvbuf);
    if (link->node)
        link->node->link = NULL;
    close(link->fd);
    zfree(link);
}