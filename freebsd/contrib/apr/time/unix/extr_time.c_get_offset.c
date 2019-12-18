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
struct tm {scalar_t__ tm_isdst; scalar_t__ __tm_gmtoff; scalar_t__ tm_gmtoff; } ;
typedef  scalar_t__ apr_int32_t ;

/* Variables and functions */
 scalar_t__ daylightOffset ; 
 scalar_t__ daylightOnOff ; 
 scalar_t__ server_gmt_offset ; 

__attribute__((used)) static apr_int32_t get_offset(struct tm *tm)
{
#if defined(HAVE_STRUCT_TM_TM_GMTOFF)
    return tm->tm_gmtoff;
#elif defined(HAVE_STRUCT_TM___TM_GMTOFF)
    return tm->__tm_gmtoff;
#else
#ifdef NETWARE
    /* Need to adjust the global variable each time otherwise
        the web server would have to be restarted when daylight
        savings changes.
    */
    if (daylightOnOff) {
        return server_gmt_offset + daylightOffset;
    }
#else
    if (tm->tm_isdst)
        return server_gmt_offset + 3600;
#endif
    return server_gmt_offset;
#endif
}