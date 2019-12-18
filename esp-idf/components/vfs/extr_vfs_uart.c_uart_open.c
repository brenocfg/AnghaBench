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
 int /*<<< orphan*/  ENOENT ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__** s_ctx ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int uart_open(const char * path, int flags, int mode)
{
    // this is fairly primitive, we should check if file is opened read only,
    // and error out if write is requested
    int fd = -1;

    if (strcmp(path, "/0") == 0) {
        fd = 0;
    } else if (strcmp(path, "/1") == 0) {
        fd = 1;
    } else if (strcmp(path, "/2") == 0) {
        fd = 2;
    } else {
        errno = ENOENT;
        return fd;
    }

    s_ctx[fd]->non_blocking = ((flags & O_NONBLOCK) == O_NONBLOCK);

    return fd;
}