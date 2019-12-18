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
 int APR_TIME_C (int) ; 
 int apr_time_now () ; 

__attribute__((used)) static void get_system_time(apr_uint64_t *uuid_time)
{
    /* ### fix this call to be more portable? */
    *uuid_time = apr_time_now();

    /* Offset between UUID formatted times and Unix formatted times.
       UUID UTC base time is October 15, 1582.
       Unix base time is January 1, 1970.      */
    *uuid_time = (*uuid_time * 10) + APR_TIME_C(0x01B21DD213814000);
}