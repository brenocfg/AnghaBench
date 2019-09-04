#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* str; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (TYPE_1__*,char const,int) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static const char *flat_escape_value_str(AVBPrint *dst, const char *src)
{
    const char *p;

    for (p = src; *p; p++) {
        switch (*p) {
        case '\n': av_bprintf(dst, "%s", "\\n");  break;
        case '\r': av_bprintf(dst, "%s", "\\r");  break;
        case '\\': av_bprintf(dst, "%s", "\\\\"); break;
        case '"':  av_bprintf(dst, "%s", "\\\""); break;
        case '`':  av_bprintf(dst, "%s", "\\`");  break;
        case '$':  av_bprintf(dst, "%s", "\\$");  break;
        default:   av_bprint_chars(dst, *p, 1);   break;
        }
    }
    return dst->str;
}