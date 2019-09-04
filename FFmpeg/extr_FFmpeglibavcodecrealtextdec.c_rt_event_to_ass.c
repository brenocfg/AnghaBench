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
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,char const,int) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*) ; 
 int av_isspace (char const) ; 
 int /*<<< orphan*/  av_strncasecmp (char const*,char*,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int rt_event_to_ass(AVBPrint *buf, const char *p)
{
    int prev_chr_is_space = 1;

    while (*p) {
        if (*p != '<') {
            if (!av_isspace(*p))
                av_bprint_chars(buf, *p, 1);
            else if (!prev_chr_is_space)
                av_bprint_chars(buf, ' ', 1);
            prev_chr_is_space = av_isspace(*p);
        } else {
            const char *end = strchr(p, '>');
            if (!end)
                break;
            if (!av_strncasecmp(p, "<br/>", 5) ||
                !av_strncasecmp(p, "<br>",  4)) {
                av_bprintf(buf, "\\N");
            }
            p = end;
        }
        p++;
    }
    return 0;
}