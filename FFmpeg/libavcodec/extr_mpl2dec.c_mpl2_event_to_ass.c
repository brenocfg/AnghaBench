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
 scalar_t__ strchr (char*,char const) ; 

__attribute__((used)) static int mpl2_event_to_ass(AVBPrint *buf, const char *p)
{
    if (*p == ' ')
        p++;

    while (*p) {
        int got_style = 0;

        while (*p && strchr("/\\_", *p)) {
            if      (*p == '/')  av_bprintf(buf, "{\\i1}");
            else if (*p == '\\') av_bprintf(buf, "{\\b1}");
            else if (*p == '_')  av_bprintf(buf, "{\\u1}");
            got_style = 1;
            p++;
        }

        while (*p && *p != '|') {
            if (*p != '\r' && *p != '\n')
                av_bprint_chars(buf, *p, 1);
            p++;
        }

        if (*p == '|') {
            if (got_style)
                av_bprintf(buf, "{\\r}");
            av_bprintf(buf, "\\N");
            p++;
        }
    }

    return 0;
}