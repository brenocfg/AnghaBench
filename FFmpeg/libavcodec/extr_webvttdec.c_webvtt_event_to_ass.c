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
struct TYPE_3__ {char* from; int /*<<< orphan*/  to; } ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,char const,int) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,...) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t const) ; 
 TYPE_1__* webvtt_tag_replace ; 

__attribute__((used)) static int webvtt_event_to_ass(AVBPrint *buf, const char *p)
{
    int i, again = 0, skip = 0;

    while (*p) {

        for (i = 0; i < FF_ARRAY_ELEMS(webvtt_tag_replace); i++) {
            const char *from = webvtt_tag_replace[i].from;
            const size_t len = strlen(from);
            if (!strncmp(p, from, len)) {
                av_bprintf(buf, "%s", webvtt_tag_replace[i].to);
                p += len;
                again = 1;
                break;
            }
        }
        if (!*p)
            break;

        if (again) {
            again = 0;
            skip = 0;
            continue;
        }
        if (*p == '<')
            skip = 1;
        else if (*p == '>')
            skip = 0;
        else if (p[0] == '\n' && p[1])
            av_bprintf(buf, "\\N");
        else if (!skip && *p != '\r')
            av_bprint_chars(buf, *p, 1);
        p++;
    }
    return 0;
}