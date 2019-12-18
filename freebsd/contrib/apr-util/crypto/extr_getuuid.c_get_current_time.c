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
typedef  scalar_t__ apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_system_time (scalar_t__*) ; 

__attribute__((used)) static void get_current_time(apr_uint64_t *timestamp)
{
    /* ### this needs to be made thread-safe! */

    apr_uint64_t time_now;
    static apr_uint64_t time_last = 0;
    static apr_uint64_t fudge = 0;

    get_system_time(&time_now);
        
    /* if clock reading changed since last UUID generated... */
    if (time_last != time_now) {
        /* The clock reading has changed since the last UUID was generated.
           Reset the fudge factor. if we are generating them too fast, then
           the fudge may need to be reset to something greater than zero. */
        if (time_last + fudge > time_now)
            fudge = time_last + fudge - time_now + 1;
        else
            fudge = 0;
        time_last = time_now;
    }
    else {
        /* We generated two really fast. Bump the fudge factor. */
        ++fudge;
    }

    *timestamp = time_now + fudge;
}