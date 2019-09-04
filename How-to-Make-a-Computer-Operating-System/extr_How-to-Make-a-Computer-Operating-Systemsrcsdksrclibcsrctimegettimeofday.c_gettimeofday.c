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
typedef  int uint64_t ;
struct timezone {int dummy; } ;
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_get_system_time ; 
 int syscall1 (int /*<<< orphan*/ ,int) ; 

int gettimeofday( struct timeval* tv, struct timezone* tz ) {
    int ret;
    uint64_t time;

    ret = syscall1( SYS_get_system_time, ( int )&time );

    if ( ret >= 0 ) {
        if ( tv != NULL ) {
            tv->tv_sec = time / 1000000;
            tv->tv_usec = time % 1000000;
        }
    }

    return ret;
}