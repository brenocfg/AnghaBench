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
typedef  int apr_uint64_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_generate_random_bytes (unsigned char*,int) ; 
 int apr_time_now () ; 
 int rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 

__attribute__((used)) static int true_random(void)
{
    apr_uint64_t time_now;

#if APR_HAS_RANDOM
    unsigned char buf[2];

    if (apr_generate_random_bytes(buf, 2) == APR_SUCCESS) {
        return (buf[0] << 8) | buf[1];
    }
#endif

    /* crap. this isn't crypto quality, but it will be Good Enough */

    time_now = apr_time_now();
    srand((unsigned int)(((time_now >> 32) ^ time_now) & 0xffffffff));

    return rand() & 0x0FFFF;
}