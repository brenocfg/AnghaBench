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
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ errno ; 
 scalar_t__ exit_signal_received ; 
 scalar_t__ poll (struct pollfd*,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ read (int const,unsigned char*,size_t) ; 

ssize_t safe_read(const int fd, void *const buf_, size_t count, const int timeout)
{
    struct pollfd  pfd;
    unsigned char *buf    = (unsigned char *) buf_;
    ssize_t        readnb = (ssize_t) -1;

    while (readnb != 0 && count > (ssize_t) 0) {
        while ((readnb = read(fd, buf, count)) < (ssize_t) 0) {
            if (errno == EAGAIN) {
                pfd.fd     = fd;
                pfd.events = POLLIN;
                if (poll(&pfd, (nfds_t) 1, timeout) <= 0) {
                    return (ssize_t) -1;
                }
            } else if (errno != EINTR || exit_signal_received) {
                return (ssize_t) -1;
            }
        }
        count -= readnb;
        buf += readnb;
    }
    return (ssize_t)(buf - (unsigned char *) buf_);
}