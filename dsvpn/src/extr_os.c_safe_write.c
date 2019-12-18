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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  nfds_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  POLLOUT ; 
 scalar_t__ errno ; 
 scalar_t__ exit_signal_received ; 
 scalar_t__ poll (struct pollfd*,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ write (int const,char const*,size_t) ; 

ssize_t safe_write(const int fd, const void *const buf_, size_t count, const int timeout)
{
    struct pollfd pfd;
    const char *  buf = (const char *) buf_;
    ssize_t       written;

    while (count > (size_t) 0) {
        while ((written = write(fd, buf, count)) < (ssize_t) 0) {
            if (errno == EAGAIN) {
                pfd.fd     = fd;
                pfd.events = POLLOUT;
                if (poll(&pfd, (nfds_t) 1, timeout) <= 0) {
                    return (ssize_t) -1;
                }
            } else if (errno != EINTR || exit_signal_received) {
                return (ssize_t) -1;
            }
        }
        buf += written;
        count -= written;
    }
    return (ssize_t)(buf - (const char *) buf_);
}