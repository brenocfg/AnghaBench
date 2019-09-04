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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int,char*,char const*,char*) ; 
 int av_log_get_level () ; 
 int /*<<< orphan*/  ff_data_to_hex (char*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void hex_log(AVFormatContext *s, int level,
                    const char *name, const uint8_t *value, int len)
{
    char buf[33];
    len = FFMIN(len, 16);
    if (av_log_get_level() < level)
        return;
    ff_data_to_hex(buf, value, len, 1);
    buf[len << 1] = '\0';
    av_log(s, level, "%s: %s\n", name, buf);
}