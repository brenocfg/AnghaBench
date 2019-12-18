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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int int64 ;

/* Variables and functions */
 int gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int warnx (char*) ; 

int64
nanoseconds(void)
{
    int r;
    struct timeval tv;

    r = gettimeofday(&tv, 0);
    if (r != 0) return warnx("gettimeofday"), -1; // can't happen

    return ((int64)tv.tv_sec)*1000000000 + ((int64)tv.tv_usec)*1000;
}