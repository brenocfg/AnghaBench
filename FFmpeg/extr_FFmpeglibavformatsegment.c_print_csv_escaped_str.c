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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,char const) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static void print_csv_escaped_str(AVIOContext *ctx, const char *str)
{
    int needs_quoting = !!str[strcspn(str, "\",\n\r")];

    if (needs_quoting)
        avio_w8(ctx, '"');

    for (; *str; str++) {
        if (*str == '"')
            avio_w8(ctx, '"');
        avio_w8(ctx, *str);
    }
    if (needs_quoting)
        avio_w8(ctx, '"');
}