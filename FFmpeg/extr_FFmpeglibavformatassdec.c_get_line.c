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
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  av_bprint_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_text_pos (int /*<<< orphan*/ *) ; 
 char ff_text_r8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t get_line(AVBPrint *buf, FFTextReader *tr)
{
    int64_t pos = ff_text_pos(tr);

    av_bprint_clear(buf);
    for (;;) {
        char c = ff_text_r8(tr);
        if (!c)
            break;
        av_bprint_chars(buf, c, 1);
        if (c == '\n')
            break;
    }
    return pos;
}