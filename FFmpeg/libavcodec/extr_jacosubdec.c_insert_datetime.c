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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ strftime (char*,int,char const*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int insert_datetime(AVBPrint *dst, const char *in, const char *arg)
{
    char buf[16] = {0};
    time_t now = time(0);
    struct tm ltime;

    localtime_r(&now, &ltime);
    if (strftime(buf, sizeof(buf), arg, &ltime))
        av_bprintf(dst, "%s", buf);
    return 0;
}