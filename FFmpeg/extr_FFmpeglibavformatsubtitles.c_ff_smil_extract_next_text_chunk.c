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
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,char,int) ; 
 char ff_text_r8 (int /*<<< orphan*/ *) ; 

int ff_smil_extract_next_text_chunk(FFTextReader *tr, AVBPrint *buf, char *c)
{
    int i = 0;
    char end_chr;

    if (!*c) // cached char?
        *c = ff_text_r8(tr);
    if (!*c)
        return 0;

    end_chr = *c == '<' ? '>' : '<';
    do {
        av_bprint_chars(buf, *c, 1);
        *c = ff_text_r8(tr);
        i++;
    } while (*c != end_chr && *c);
    if (end_chr == '>') {
        av_bprint_chars(buf, '>', 1);
        *c = 0;
    }
    return i;
}