#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ error; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 scalar_t__ AVERROR_EOF ; 
 int /*<<< orphan*/  av_bprint_append_data (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ avio_feof (TYPE_1__*) ; 
 char avio_r8 (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_skip (TYPE_1__*,int) ; 

__attribute__((used)) static int64_t read_line_to_bprint_escaped(AVIOContext *s, AVBPrint *bp)
{
    int len, end;
    int64_t read = 0;
    char tmp[1024];
    char c;
    char prev = ' ';

    do {
        len = 0;
        do {
            c = avio_r8(s);
            end = prev != '\\' && (c == '\r' || c == '\n' || c == '\0');
            if (!end)
                tmp[len++] = c;
            prev = c;
        } while (!end && len < sizeof(tmp));
        av_bprint_append_data(bp, tmp, len);
        read += len;
    } while (!end);

    if (c == '\r' && avio_r8(s) != '\n' && !avio_feof(s))
        avio_skip(s, -1);

    if (!c && s->error)
        return s->error;

    if (!c && !read && avio_feof(s))
        return AVERROR_EOF;

    return read;
}