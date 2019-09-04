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
struct tm {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int INT64_C (int) ; 
 int /*<<< orphan*/  av_small_strptime (char const*,char*,struct tm*) ; 
 int av_timegm (struct tm*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int64_t ftp_parse_date(const char *date)
{
    struct tm tv;
    memset(&tv, 0, sizeof(struct tm));
    av_small_strptime(date, "%Y%m%d%H%M%S", &tv);
    return INT64_C(1000000) * av_timegm(&tv);
}