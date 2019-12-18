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
typedef  long long int64_t ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 long long INT64_MAX ; 
 long long INT64_MIN ; 
 long long TSBASE ; 
 int av_sscanf (char const*,char*,long long*,int*,long long*,int*) ; 

__attribute__((used)) static int parse_line(const char *line, int64_t *value, int64_t *value2)
{
    int vi, p1, p2;

    for (vi = 0; vi < 2; vi++) {
        long long intval, fracval;
        int n = av_sscanf(line, "%lld%n.%lld%n", &intval, &p1, &fracval, &p2);
        if (n <= 0 || intval < INT64_MIN / TSBASE || intval > INT64_MAX / TSBASE)
            return AVERROR_INVALIDDATA;

        intval *= TSBASE;

        if (n == 2) {
            if (fracval < 0)
                return AVERROR_INVALIDDATA;
            for (;p2 - p1 < 7 + 1; p1--)
                fracval *= 10;
            for (;p2 - p1 > 7 + 1; p1++)
                fracval /= 10;
            if (intval > 0) intval += fracval;
            else            intval -= fracval;
            line += p2;
        } else
            line += p1;

        *value = intval;

        value = value2;
    }

    return 0;
}