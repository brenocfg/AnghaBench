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
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ nanosleep (struct timespec*,struct timespec*) ; 

__attribute__((used)) static inline int proc_sleep (int timeout)
{
    assert(timeout > 0);
    struct timespec sleepns, remns;
    sleepns.tv_sec = timeout / 1000;
    sleepns.tv_nsec = (timeout % 1000) * 1000000;
    while(nanosleep(&sleepns, &remns) && errno == EINTR)
        sleepns = remns;
    return(1);
}