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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static void write_escape_str(AVIOContext *s, const uint8_t *str)
{
    const uint8_t *p = str;

    while (*p) {
        if (*p == '#' || *p == ';' || *p == '=' || *p == '\\' || *p == '\n')
            avio_w8(s, '\\');
        avio_w8(s, *p);
        p++;
    }
}