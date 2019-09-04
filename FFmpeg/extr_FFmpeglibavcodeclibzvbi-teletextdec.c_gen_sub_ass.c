#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int columns; int pgno; int rows; TYPE_2__* text; } ;
typedef  TYPE_1__ vbi_page ;
typedef  int /*<<< orphan*/  vbi_color ;
struct TYPE_20__ {scalar_t__ opacity; } ;
typedef  TYPE_2__ vbi_char ;
struct TYPE_21__ {int* subtitle_map; int last_ass_alignment; int /*<<< orphan*/  readorder; } ;
typedef  TYPE_3__ TeletextContext ;
struct TYPE_23__ {int /*<<< orphan*/  str; scalar_t__ len; } ;
struct TYPE_22__ {int /*<<< orphan*/  type; int /*<<< orphan*/  ass; } ;
typedef  TYPE_4__ AVSubtitleRect ;
typedef  TYPE_5__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFABS (int) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  SUBTITLE_ASS ; 
 int /*<<< orphan*/  SUBTITLE_NONE ; 
 int /*<<< orphan*/  VBI_BLACK ; 
 scalar_t__ VBI_TRANSPARENT_SPACE ; 
 int /*<<< orphan*/  VBI_WHITE ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_is_complete (TYPE_5__*) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_5__*,char*,...) ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_string (TYPE_1__*,TYPE_2__*,TYPE_5__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_ass_get_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_trim_info (TYPE_1__*,TYPE_2__*,int*,int*,int*) ; 

__attribute__((used)) static int gen_sub_ass(TeletextContext *ctx, AVSubtitleRect *sub_rect, vbi_page *page, int chop_top)
{
    int i;
    int leading, trailing, len;
    int last_trailing = -1, last_leading = -1;
    int min_trailing = page->columns, min_leading = page->columns;
    int alignment = 2;
    int vertical_align = -1;
    int can_align_left = 1, can_align_right = 1, can_align_center = 1;
    int is_subtitle_page = ctx->subtitle_map[page->pgno & 0x7ff];
    int empty_lines = 0;
    vbi_color cur_color = VBI_WHITE;
    vbi_color cur_back_color = VBI_BLACK;
    AVBPrint buf;

    av_bprint_init(&buf, 0, AV_BPRINT_SIZE_UNLIMITED);

    for (i = chop_top; i < page->rows; i++) {
        vbi_char *row = page->text + i * page->columns;

        get_trim_info(page, row, &leading, &trailing, &len);

        if (len) {
            if (last_leading != -1 && last_leading != leading || leading > 5)
                can_align_left = 0;
            if (last_trailing != -1 && last_trailing != trailing || trailing > 2)
                can_align_right = 0;
            if (last_trailing != -1 && (FFABS((trailing - leading) - (last_trailing - last_leading)) > 1) || trailing - leading > 4)
                can_align_center = 0;
            last_leading = leading;
            last_trailing = trailing;
            min_leading = FFMIN(leading, min_leading);
            min_trailing = FFMIN(trailing, min_trailing);
        }
    }

    if (!can_align_right && can_align_left && !can_align_center) {
        ctx->last_ass_alignment = alignment = 1;
    } else if (!can_align_right && !can_align_left && can_align_center) {
        ctx->last_ass_alignment = alignment = 2;
    } else if (can_align_right && !can_align_left && !can_align_center) {
        ctx->last_ass_alignment = alignment = 3;
    } else {
        if (ctx->last_ass_alignment == 1 && can_align_left ||
            ctx->last_ass_alignment == 2 && can_align_center ||
            ctx->last_ass_alignment == 3 && can_align_right)
            alignment = ctx->last_ass_alignment;
    }

    for (i = chop_top; i < page->rows; i++) {
        int j;
        vbi_char *row = page->text + i * page->columns;
        int is_transparent_line;

        for (j = 0; j < page->columns; j++)
            if (row[j].opacity != VBI_TRANSPARENT_SPACE)
                break;
        is_transparent_line = (j == page->columns);

        len = is_transparent_line ? 0 : page->columns;
        leading = trailing = is_transparent_line ? page->columns : 0;

        if (is_subtitle_page) {
            if (!is_transparent_line)
                get_trim_info(page, row, &leading, &trailing, &len);

            if (vertical_align == -1 && len) {
                vertical_align = (2 - (av_clip(i + 1, 0, 23) / 8));
                av_bprintf(&buf, "{\\an%d}", alignment + vertical_align * 3);
                if (vertical_align != 2)
                    empty_lines = 0;
            }

            if (len && empty_lines > 1)
                for (empty_lines /= 2; empty_lines > 0; empty_lines--)
                    av_bprintf(&buf, " \\N");

            if (alignment == 1 || alignment == 2 && !can_align_center)
                leading = min_leading;
            if (alignment == 3 || alignment == 2 && !can_align_center)
                trailing = min_trailing;
        }

        if (len || !is_subtitle_page) {
            decode_string(page, row, &buf, leading, page->columns - trailing, &cur_color, &cur_back_color);
            av_bprintf(&buf, " \\N");
            empty_lines = 0;
        } else {
            empty_lines++;
        }
    }

    if (vertical_align == 0)
        for (empty_lines = (empty_lines - 1) / 2; empty_lines > 0; empty_lines--)
            av_bprintf(&buf, " \\N");

    if (!av_bprint_is_complete(&buf)) {
        av_bprint_finalize(&buf, NULL);
        return AVERROR(ENOMEM);
    }

    if (buf.len) {
        sub_rect->type = SUBTITLE_ASS;
        sub_rect->ass = ff_ass_get_dialog(ctx->readorder++, 0, is_subtitle_page ? "Subtitle" : "Teletext", NULL, buf.str);

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