#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* state; int /*<<< orphan*/  display; } ;
typedef  TYPE_4__ zbar_processor_t ;
struct TYPE_8__ {TYPE_1__* fds; } ;
struct TYPE_9__ {TYPE_2__ polling; } ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  XProcessInternalConnection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_connection_handler (TYPE_4__*,int) ; 

__attribute__((used)) static int x_internal_handler (zbar_processor_t *proc,
                               int i)
{
    XProcessInternalConnection(proc->display, proc->state->polling.fds[i].fd);
    x_connection_handler(proc, i);
    return(0);
}