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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  WriterContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  PRINT_STRING_OPT ; 
 int /*<<< orphan*/  writer_print_integer (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  writer_print_string (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writer_print_ts(WriterContext *wctx, const char *key, int64_t ts, int is_duration)
{
    if ((!is_duration && ts == AV_NOPTS_VALUE) || (is_duration && ts == 0)) {
        writer_print_string(wctx, key, "N/A", PRINT_STRING_OPT);
    } else {
        writer_print_integer(wctx, key, ts);
    }
}