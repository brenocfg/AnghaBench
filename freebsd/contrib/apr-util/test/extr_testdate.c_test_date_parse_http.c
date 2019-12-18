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
typedef  int time_t ;
typedef  int /*<<< orphan*/  guess ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int apr_time_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_TRUE (int /*<<< orphan*/ *,int) ; 
 int APR_TIME_C (int) ; 
 int APR_USEC_PER_SEC ; 
 int apr_date_parse_http (char*) ; 
 int /*<<< orphan*/  apr_generate_random_bytes (unsigned char*,int) ; 
 int apr_time_now () ; 
 int /*<<< orphan*/  gm_timestr_822 (char*,int) ; 
 scalar_t__ lgc (int /*<<< orphan*/ ) ; 
 int* year2secs ; 

__attribute__((used)) static void test_date_parse_http(abts_case *tc, void *data)
{
    int year, i;
    apr_time_t guess;
    apr_time_t offset = 0;
    apr_time_t secstodate, newsecs;
    char datestr[50];

    for (year = 1970; year < 2038; ++year) {
        secstodate = year2secs[year - 1970] + offset;
        gm_timestr_822(datestr, secstodate);
        secstodate *= APR_USEC_PER_SEC;
        newsecs = apr_date_parse_http(datestr);
        ABTS_TRUE(tc, secstodate == newsecs);
    }

#if APR_HAS_RANDOM
    apr_generate_random_bytes((unsigned char *)&guess, sizeof(guess));
#else
    guess = apr_time_now() % APR_TIME_C(4294967291);
#endif

    for (i = 0; i < 10000; ++i) {
        guess = (time_t)lgc((apr_uint32_t)guess);
        if (guess < 0)
            guess *= -1;
        secstodate = guess + offset;
        gm_timestr_822(datestr, secstodate);
        secstodate *= APR_USEC_PER_SEC;
        newsecs = apr_date_parse_http(datestr);
        ABTS_TRUE(tc, secstodate == newsecs);
    }
}