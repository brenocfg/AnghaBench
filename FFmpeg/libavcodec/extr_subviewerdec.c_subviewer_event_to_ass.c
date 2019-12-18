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
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int subviewer_event_to_ass(AVBPrint *buf, const char *p)
{
    while (*p) {
        if (!strncmp(p, "[br]", 4)) {
            av_bprintf(buf, "\\N");
            p += 4;
        } else {
            if (p[0] == '\n' && p[1])
                av_bprintf(buf, "\\N");
            else if (*p != '\n' && *p != '\r')
                av_bprint_chars(buf, *p, 1);
            p++;
        }
    }

    return 0;
}