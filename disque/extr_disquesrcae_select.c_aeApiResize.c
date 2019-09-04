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
typedef  int /*<<< orphan*/  aeEventLoop ;

/* Variables and functions */
 int FD_SETSIZE ; 

__attribute__((used)) static int aeApiResize(aeEventLoop *eventLoop, int setsize) {
    /* Just ensure we have enough room in the fd_set type. */
    if (setsize >= FD_SETSIZE) return -1;
    return 0;
}