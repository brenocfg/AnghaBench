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
struct timespec {scalar_t__ tv_nsec; int tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static void timespec_add_nano(struct timespec * out, struct timespec * in, long val)
{
    out->tv_nsec = val + in->tv_nsec;
    if (out->tv_nsec < (in->tv_nsec)) {
        out->tv_sec += 1;
    }
}