#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ rows; int /*<<< orphan*/  columns; } ;
typedef  TYPE_1__ vbi_page ;
struct TYPE_17__ {scalar_t__ chop_spaces; } ;
typedef  TYPE_2__ TeletextContext ;
struct TYPE_19__ {int /*<<< orphan*/  str; scalar_t__ len; } ;
struct TYPE_18__ {int /*<<< orphan*/  type; int /*<<< orphan*/  ass; } ;
typedef  TYPE_3__ AVSubtitleRect ;
typedef  TYPE_4__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SUBTITLE_ASS ; 
 int /*<<< orphan*/  SUBTITLE_NONE ; 
 scalar_t__ TEXT_MAXSZ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  av_bprint_append_data (TYPE_4__*,char const*,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  av_bprint_is_complete (TYPE_4__*) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_malloc (scalar_t__) ; 
 int chop_spaces_utf8 (char const*,int) ; 
 int /*<<< orphan*/  create_ass_text (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 
 int vbi_print_page_region (TYPE_1__*,char*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gen_sub_text(TeletextContext *ctx, AVSubtitleRect *sub_rect, vbi_page *page, int chop_top)
{
    const char *in;
    AVBPrint buf;
    char *vbi_text = av_malloc(TEXT_MAXSZ);
    int sz;

    if (!vbi_text)
        return AVERROR(ENOMEM);

    sz = vbi_print_page_region(page, vbi_text, TEXT_MAXSZ-1, "UTF-8",
                                   /*table mode*/ TRUE, FALSE,
                                   0,             chop_top,
                                   page->columns, page->rows-chop_top);
    if (sz <= 0) {
        av_log(ctx, AV_LOG_ERROR, "vbi_print error\n");
        av_free(vbi_text);
        return AVERROR_EXTERNAL;
    }
    vbi_text[sz] = '\0';
    in  = vbi_text;
    av_bprint_init(&buf, 0, TEXT_MAXSZ);

    if (ctx->chop_spaces) {
        for (;;) {
            int nl, sz;

            // skip leading spaces and newlines
            in += strspn(in, " \n");
            // compute end of row
            for (nl = 0; in[nl]; ++nl)
                if (in[nl] == '\n' && (nl==0 || !(in[nl-1] & 0x80)))
                    break;
            if (!in[nl])
                break;
            // skip trailing spaces
            sz = chop_spaces_utf8(in, nl);
            av_bprint_append_data(&buf, in, sz);
            av_bprintf(&buf, "\n");
            in += nl;
        }
    } else {
        av_bprintf(&buf, "%s\n", vbi_text);
    }
    av_free(vbi_text);

    if (!av_bprint_is_complete(&buf)) {
        av_bprint_finalize(&buf, NULL);
        return AVERROR(ENOMEM);
    }

    if (buf.len) {
        sub_rect->type = SUBTITLE_ASS;
        sub_rect->ass = create_ass_text(ctx, buf.str);

        if (!sub_rect->ass) {
            av_bprint_finalize(&buf, NULL);
            return AVERROR(ENOMEM);
        }
        av_log(ctx, AV_LOG_DEBUG, "subtext:%s:txetbus\n", sub_rect->ass);
    } else {
        sub_rect->type = SUBTITLE_NONE;
    }
    av_bprint_finalize(&buf, NULL);
    return 0;
}