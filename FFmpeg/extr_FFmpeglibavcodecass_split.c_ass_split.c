#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  section; } ;
struct TYPE_6__ {int current_section; } ;
typedef  TYPE_1__ ASSSplitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FF_ARRAY_ELEMS (TYPE_4__*) ; 
 TYPE_4__* ass_sections ; 
 char* ass_split_section (TYPE_1__*,char const*) ; 
 int sscanf (char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcspn (char const*,char*) ; 

__attribute__((used)) static int ass_split(ASSSplitContext *ctx, const char *buf)
{
    char c, section[16];
    int i;

    if (ctx->current_section >= 0)
        buf = ass_split_section(ctx, buf);

    while (buf && *buf) {
        if (sscanf(buf, "[%15[0-9A-Za-z+ ]]%c", section, &c) == 2) {
            buf += strcspn(buf, "\n");
            buf += !!*buf;
            for (i=0; i<FF_ARRAY_ELEMS(ass_sections); i++)
                if (!strcmp(section, ass_sections[i].section)) {
                    ctx->current_section = i;
                    buf = ass_split_section(ctx, buf);
                }
        } else {
            buf += strcspn(buf, "\n");
            buf += !!*buf;
        }
    }
    return buf ? 0 : AVERROR_INVALIDDATA;
}