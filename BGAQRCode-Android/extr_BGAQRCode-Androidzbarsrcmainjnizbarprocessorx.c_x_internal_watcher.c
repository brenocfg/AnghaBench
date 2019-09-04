#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_processor_t ;
typedef  scalar_t__ XPointer ;
typedef  int /*<<< orphan*/  Display ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int /*<<< orphan*/  add_poll (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_poll (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  x_internal_handler ; 

__attribute__((used)) static void x_internal_watcher (Display *display,
                                XPointer client_arg,
                                int fd,
                                Bool opening,
                                XPointer *watch_arg)
{
    zbar_processor_t *proc = (void*)client_arg;
    if(opening)
        add_poll(proc, fd, x_internal_handler);
    else
        remove_poll(proc, fd);
}