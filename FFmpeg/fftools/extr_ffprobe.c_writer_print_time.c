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
struct TYPE_2__ {double d; } ;
struct unit_value {int /*<<< orphan*/  unit; TYPE_1__ val; } ;
typedef  double int64_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WriterContext ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 double AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  PRINT_STRING_OPT ; 
 double av_q2d (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  unit_second_str ; 
 int /*<<< orphan*/  value_string (char*,int,struct unit_value) ; 
 int /*<<< orphan*/  writer_print_string (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writer_print_time(WriterContext *wctx, const char *key,
                              int64_t ts, const AVRational *time_base, int is_duration)
{
    char buf[128];

    if ((!is_duration && ts == AV_NOPTS_VALUE) || (is_duration && ts == 0)) {
        writer_print_string(wctx, key, "N/A", PRINT_STRING_OPT);
    } else {
        double d = ts * av_q2d(*time_base);
        struct unit_value uv;
        uv.val.d = d;
        uv.unit = unit_second_str;
        value_string(buf, sizeof(buf), uv);
        writer_print_string(wctx, key, buf, 0);
    }
}