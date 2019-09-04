#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_9__ {int /*<<< orphan*/  monitors; } ;
struct TYPE_8__ {int /*<<< orphan*/  ok; } ;

/* Variables and functions */
 int CLIENT_MONITOR ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_3__ server ; 
 TYPE_2__ shared ; 

void monitorCommand(client *c) {
    /* ignore MONITOR if already slave or in monitor mode */
    if (c->flags & CLIENT_MONITOR) return;

    c->flags |= CLIENT_MONITOR;
    listAddNodeTail(server.monitors,c);
    addReply(c,shared.ok);
}