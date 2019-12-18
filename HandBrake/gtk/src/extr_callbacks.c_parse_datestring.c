#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  maps ;
struct TYPE_2__ {char* member_0; char* member_1; int /*<<< orphan*/  format; int /*<<< orphan*/  pattern; } ;
typedef  TYPE_1__ datemap ;

/* Variables and functions */
 int /*<<< orphan*/  av_small_strptime (char const*,int /*<<< orphan*/ ,struct tm*) ; 
 scalar_t__ hb_validate_param_string (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
parse_datestring(const char *src, struct tm *tm)
{
    datemap ymdThmsZ = {"[0-9]{4}-[0-1]?[0-9]-[0-3]?[0-9]T[0-9]{2}:[0-9]{2}:[0-9]{2}Z", "%Y-%m-%dT%H:%M:%SZ"};

    datemap maps[1] = { ymdThmsZ };

    for (int i = 0; i < sizeof(maps); i++)
    {
        if (hb_validate_param_string(maps[i].pattern, src))
        {
            av_small_strptime(src, maps[i].format, tm);
            return 1;
        }
    }
    return 0;
}