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
struct TYPE_5__ {char* str; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_1__*,char*,...) ; 

__attribute__((used)) static char *ini_escape_str(AVBPrint *dst, const char *src)
{
    int i = 0;
    char c = 0;

    while (c = src[i++]) {
        switch (c) {
        case '\b': av_bprintf(dst, "%s", "\\b"); break;
        case '\f': av_bprintf(dst, "%s", "\\f"); break;
        case '\n': av_bprintf(dst, "%s", "\\n"); break;
        case '\r': av_bprintf(dst, "%s", "\\r"); break;
        case '\t': av_bprintf(dst, "%s", "\\t"); break;
        case '\\':
        case '#' :
        case '=' :
        case ':' : av_bprint_chars(dst, '\\', 1);
        default:
            if ((unsigned char)c < 32)
                av_bprintf(dst, "\\x00%02x", c & 0xff);
            else
                av_bprint_chars(dst, c, 1);
            break;
        }
    }
    return dst->str;
}