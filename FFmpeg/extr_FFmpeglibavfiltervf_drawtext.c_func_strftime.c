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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_strftime (int /*<<< orphan*/ *,char const*,struct tm*) ; 
 struct tm* gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int func_strftime(AVFilterContext *ctx, AVBPrint *bp,
                         char *fct, unsigned argc, char **argv, int tag)
{
    const char *fmt = argc ? argv[0] : "%Y-%m-%d %H:%M:%S";
    time_t now;
    struct tm tm;

    time(&now);
    if (tag == 'L')
        localtime_r(&now, &tm);
    else
        tm = *gmtime_r(&now, &tm);
    av_bprint_strftime(bp, fmt, &tm);
    return 0;
}