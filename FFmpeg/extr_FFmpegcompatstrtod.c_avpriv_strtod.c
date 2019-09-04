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

/* Variables and functions */
 double INFINITY ; 
 double NAN ; 
 scalar_t__ av_isspace (char const) ; 
 int /*<<< orphan*/  av_strncasecmp (char const*,char*,int) ; 
 char* check_nan_suffix (char const*) ; 
 double strtod (char const*,char**) ; 
 double strtoll (char const*,char**,int) ; 

double avpriv_strtod(const char *nptr, char **endptr)
{
    const char *end;
    double res;

    /* Skip leading spaces */
    while (av_isspace(*nptr))
        nptr++;

    if (!av_strncasecmp(nptr, "infinity", 8)) {
        end = nptr + 8;
        res = INFINITY;
    } else if (!av_strncasecmp(nptr, "inf", 3)) {
        end = nptr + 3;
        res = INFINITY;
    } else if (!av_strncasecmp(nptr, "+infinity", 9)) {
        end = nptr + 9;
        res = INFINITY;
    } else if (!av_strncasecmp(nptr, "+inf", 4)) {
        end = nptr + 4;
        res = INFINITY;
    } else if (!av_strncasecmp(nptr, "-infinity", 9)) {
        end = nptr + 9;
        res = -INFINITY;
    } else if (!av_strncasecmp(nptr, "-inf", 4)) {
        end = nptr + 4;
        res = -INFINITY;
    } else if (!av_strncasecmp(nptr, "nan", 3)) {
        end = check_nan_suffix(nptr + 3);
        res = NAN;
    } else if (!av_strncasecmp(nptr, "+nan", 4) ||
               !av_strncasecmp(nptr, "-nan", 4)) {
        end = check_nan_suffix(nptr + 4);
        res = NAN;
    } else if (!av_strncasecmp(nptr, "0x", 2) ||
               !av_strncasecmp(nptr, "-0x", 3) ||
               !av_strncasecmp(nptr, "+0x", 3)) {
        /* FIXME this doesn't handle exponents, non-integers (float/double)
         * and numbers too large for long long */
        res = strtoll(nptr, (char **)&end, 16);
    } else {
        res = strtod(nptr, (char **)&end);
    }

    if (endptr)
        *endptr = (char *)end;

    return res;
}