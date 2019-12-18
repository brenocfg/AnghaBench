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
typedef  int /*<<< orphan*/  eol_buf ;
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  av_bprint_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char ff_text_r8 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_eol (char) ; 

void ff_subtitles_read_text_chunk(FFTextReader *tr, AVBPrint *buf)
{
    char eol_buf[5], last_was_cr = 0;
    int n = 0, i = 0, nb_eol = 0;

    av_bprint_clear(buf);

    for (;;) {
        char c = ff_text_r8(tr);

        if (!c)
            break;

        /* ignore all initial line breaks */
        if (n == 0 && is_eol(c))
            continue;

        /* line break buffering: we don't want to add the trailing \r\n */
        if (is_eol(c)) {
            nb_eol += c == '\n' || last_was_cr;
            if (nb_eol == 2)
                break;
            eol_buf[i++] = c;
            if (i == sizeof(eol_buf) - 1)
                break;
            last_was_cr = c == '\r';
            continue;
        }

        /* only one line break followed by data: we flush the line breaks
         * buffer */
        if (i) {
            eol_buf[i] = 0;
            av_bprintf(buf, "%s", eol_buf);
            i = nb_eol = 0;
        }

        av_bprint_chars(buf, c, 1);
        n++;
    }
}