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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,double,char const*) ; 
 int lrintf (double) ; 

__attribute__((used)) static void print_fps(double d, const char *postfix)
{
    uint64_t v = lrintf(d * 100);
    if (!v)
        av_log(NULL, AV_LOG_INFO, "%1.4f %s", d, postfix);
    else if (v % 100)
        av_log(NULL, AV_LOG_INFO, "%3.2f %s", d, postfix);
    else if (v % (100 * 1000))
        av_log(NULL, AV_LOG_INFO, "%1.0f %s", d, postfix);
    else
        av_log(NULL, AV_LOG_INFO, "%1.0fk %s", d / 1000, postfix);
}