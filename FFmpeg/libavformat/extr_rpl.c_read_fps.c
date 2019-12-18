#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 int INT64_MAX ; 
 int /*<<< orphan*/  av_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int read_int (char const*,char const**,int*) ; 

__attribute__((used)) static AVRational read_fps(const char* line, int* error)
{
    int64_t num, den = 1;
    AVRational result;
    num = read_int(line, &line, error);
    if (*line == '.')
        line++;
    for (; *line>='0' && *line<='9'; line++) {
        // Truncate any numerator too large to fit into an int64_t
        if (num > (INT64_MAX - 9) / 10 || den > INT64_MAX / 10)
            break;
        num  = 10 * num + *line - '0';
        den *= 10;
    }
    if (!num)
        *error = -1;
    av_reduce(&result.num, &result.den, num, den, 0x7FFFFFFF);
    return result;
}