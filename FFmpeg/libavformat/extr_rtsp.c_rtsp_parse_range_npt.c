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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  SPACE_CHARS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ av_parse_time (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  av_stristart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  get_word_sep (char*,int,char*,char const**) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsp_parse_range_npt(const char *p, int64_t *start, int64_t *end)
{
    char buf[256];

    p += strspn(p, SPACE_CHARS);
    if (!av_stristart(p, "npt=", &p))
        return;

    *start = AV_NOPTS_VALUE;
    *end = AV_NOPTS_VALUE;

    get_word_sep(buf, sizeof(buf), "-", &p);
    if (av_parse_time(start, buf, 1) < 0)
        return;
    if (*p == '-') {
        p++;
        get_word_sep(buf, sizeof(buf), "-", &p);
        if (av_parse_time(end, buf, 1) < 0)
            av_log(NULL, AV_LOG_DEBUG, "Failed to parse interval end specification '%s'\n", buf);
    }
}