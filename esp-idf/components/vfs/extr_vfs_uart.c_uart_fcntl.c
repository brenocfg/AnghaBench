#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int non_blocking; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int F_GETFL ; 
 int F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__** s_ctx ; 

__attribute__((used)) static int uart_fcntl(int fd, int cmd, int arg)
{
    assert(fd >=0 && fd < 3);
    int result = 0;
    if (cmd == F_GETFL) {
        if (s_ctx[fd]->non_blocking) {
            result |= O_NONBLOCK;
        }
    } else if (cmd == F_SETFL) {
        s_ctx[fd]->non_blocking = (arg & O_NONBLOCK) != 0;
    } else {
        // unsupported operation
        result = -1;
        errno = ENOSYS;
    }
    return result;
}