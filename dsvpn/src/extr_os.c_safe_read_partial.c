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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit_signal_received ; 
 int /*<<< orphan*/  read (int const,unsigned char* const,size_t const) ; 

ssize_t safe_read_partial(const int fd, void *const buf_, const size_t max_count)
{
    unsigned char *const buf = (unsigned char *) buf_;
    ssize_t              readnb;

    while ((readnb = read(fd, buf, max_count)) < (ssize_t) 0 && errno == EINTR &&
           !exit_signal_received)
        ;
    return readnb;
}