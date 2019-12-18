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
typedef  int uint32_t ;
struct tm {int tm_year; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; scalar_t__ tm_mon; scalar_t__ tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct tm*,struct tm const*,int) ; 
 scalar_t__ mz_zip_invalid_date (struct tm*) ; 

uint32_t mz_zip_tm_to_dosdate(const struct tm *ptm)
{
    struct tm fixed_tm;

    /* Years supported: */

    /* [00, 79]      (assumed to be between 2000 and 2079) */
    /* [80, 207]     (assumed to be between 1980 and 2107, typical output of old */
    /*                software that does 'year-1900' to get a double digit year) */
    /* [1980, 2107]  (due to format limitations, only years 1980-2107 can be stored.) */

    memcpy(&fixed_tm, ptm, sizeof(struct tm));
    if (fixed_tm.tm_year >= 1980) /* range [1980, 2107] */
        fixed_tm.tm_year -= 1980;
    else if (fixed_tm.tm_year >= 80) /* range [80, 207] */
        fixed_tm.tm_year -= 80;
    else /* range [00, 79] */
        fixed_tm.tm_year += 20;

    if (mz_zip_invalid_date(&fixed_tm))
        return 0;

    return (((uint32_t)fixed_tm.tm_mday + (32 * ((uint32_t)fixed_tm.tm_mon + 1)) + (512 * (uint32_t)fixed_tm.tm_year)) << 16) |
        (((uint32_t)fixed_tm.tm_sec / 2) + (32 * (uint32_t)fixed_tm.tm_min) + (2048 * (uint32_t)fixed_tm.tm_hour));
}