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
typedef  size_t ptrdiff_t ;
typedef  int /*<<< orphan*/  FFTextReader ;

/* Variables and functions */
 size_t AVERROR_INVALIDDATA ; 
 scalar_t__ ff_text_eof (int /*<<< orphan*/ *) ; 
 char ff_text_peek_r8 (int /*<<< orphan*/ *) ; 
 unsigned char ff_text_r8 (int /*<<< orphan*/ *) ; 

ptrdiff_t ff_subtitles_read_line(FFTextReader *tr, char *buf, size_t size)
{
    size_t cur = 0;
    if (!size)
        return 0;
    while (cur + 1 < size) {
        unsigned char c = ff_text_r8(tr);
        if (!c)
            return ff_text_eof(tr) ? cur : AVERROR_INVALIDDATA;
        if (c == '\r' || c == '\n')
            break;
        buf[cur++] = c;
        buf[cur] = '\0';
    }
    while (ff_text_peek_r8(tr) == '\r')
        ff_text_r8(tr);
    if (ff_text_peek_r8(tr) == '\n')
        ff_text_r8(tr);
    return cur;
}