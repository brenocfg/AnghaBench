#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_1__ timeval_t ;
struct utimbuf {int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; } ;

/* Variables and functions */
 int utime (char const*,struct utimbuf*) ; 

int utimes( const char* filename, const timeval_t times[2] ) {
    struct utimbuf tmp;

    /* NOTE: no microsecond precision */
    tmp.actime = times[ 0 ].tv_sec;
    tmp.modtime = times[ 1 ].tv_sec;

    /* This is a wrapper around utime() */
    return utime( filename, &tmp );
}