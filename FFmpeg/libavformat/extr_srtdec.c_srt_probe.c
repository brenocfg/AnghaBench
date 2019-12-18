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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ ff_subtitles_read_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ff_text_init_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char ff_text_peek_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_text_r8 (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int*) ; 
 scalar_t__ strstr (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int srt_probe(const AVProbeData *p)
{
    int v;
    char buf[64], *pbuf;
    FFTextReader tr;

    ff_text_init_buf(&tr, p->buf, p->buf_size);

    while (ff_text_peek_r8(&tr) == '\r' || ff_text_peek_r8(&tr) == '\n')
        ff_text_r8(&tr);

    /* Check if the first non-empty line is a number. We do not check what the
     * number is because in practice it can be anything.
     * Also, that number can be followed by random garbage, so we can not
     * unfortunately check that we only have a number. */
    if (ff_subtitles_read_line(&tr, buf, sizeof(buf)) < 0 ||
        strtol(buf, &pbuf, 10) < 0 || pbuf == buf)
        return 0;

    /* Check if the next line matches a SRT timestamp */
    if (ff_subtitles_read_line(&tr, buf, sizeof(buf)) < 0)
        return 0;
    pbuf = buf;
    if (buf[0] == '-')
        pbuf++;
    if (pbuf[0] >= '0' && pbuf[0] <= '9' && strstr(buf, " --> ")
        && sscanf(buf, "%*d:%*d:%*d%*1[,.]%*d --> %*d:%*d:%*d%*1[,.]%d", &v) == 1)
        return AVPROBE_SCORE_MAX;

    return 0;
}