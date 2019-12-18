#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_6__* priv_data; } ;
struct TYPE_14__ {int hlit_start; int hlit_end; } ;
struct TYPE_13__ {int /*<<< orphan*/ * hlit_color; } ;
struct TYPE_10__ {int wrap_flag; } ;
struct TYPE_15__ {int box_flags; int style_entries; int ftab_entries; TYPE_5__ h; TYPE_4__ c; TYPE_3__** ftab; TYPE_2__** s; TYPE_1__ w; } ;
struct TYPE_12__ {scalar_t__ fontID; int /*<<< orphan*/  font; } ;
struct TYPE_11__ {int style_flag; int style_end; int style_start; scalar_t__ style_fontID; int /*<<< orphan*/  fontsize; } ;
typedef  TYPE_6__ MovTextContext ;
typedef  TYPE_7__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int HCLR_BOX ; 
 int HLIT_BOX ; 
 int STYLE_FLAG_BOLD ; 
 int STYLE_FLAG_ITALIC ; 
 int STYLE_FLAG_UNDERLINE ; 
 int STYL_BOX ; 
 int TWRP_BOX ; 
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,char const,int) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int get_utf8_length_at (char const*,char const*) ; 

__attribute__((used)) static int text_to_ass(AVBPrint *buf, const char *text, const char *text_end,
                       AVCodecContext *avctx)
{
    MovTextContext *m = avctx->priv_data;
    int i = 0;
    int j = 0;
    int text_pos = 0;

    if (text < text_end && m->box_flags & TWRP_BOX) {
        if (m->w.wrap_flag == 1) {
            av_bprintf(buf, "{\\q1}"); /* End of line wrap */
        } else {
            av_bprintf(buf, "{\\q2}"); /* No wrap */
        }
    }

    while (text < text_end) {
        int len;

        if (m->box_flags & STYL_BOX) {
            for (i = 0; i < m->style_entries; i++) {
                if (m->s[i]->style_flag && text_pos == m->s[i]->style_end) {
                    av_bprintf(buf, "{\\r}");
                }
            }
            for (i = 0; i < m->style_entries; i++) {
                if (m->s[i]->style_flag && text_pos == m->s[i]->style_start) {
                    if (m->s[i]->style_flag & STYLE_FLAG_BOLD)
                        av_bprintf(buf, "{\\b1}");
                    if (m->s[i]->style_flag & STYLE_FLAG_ITALIC)
                        av_bprintf(buf, "{\\i1}");
                    if (m->s[i]->style_flag & STYLE_FLAG_UNDERLINE)
                        av_bprintf(buf, "{\\u1}");
                    av_bprintf(buf, "{\\fs%d}", m->s[i]->fontsize);
                    for (j = 0; j < m->ftab_entries; j++) {
                        if (m->s[i]->style_fontID == m->ftab[j]->fontID)
                            av_bprintf(buf, "{\\fn%s}", m->ftab[j]->font);
                    }
                }
            }
        }
        if (m->box_flags & HLIT_BOX) {
            if (text_pos == m->h.hlit_start) {
                /* If hclr box is present, set the secondary color to the color
                 * specified. Otherwise, set primary color to white and secondary
                 * color to black. These colors will come from TextSampleModifier
                 * boxes in future and inverse video technique for highlight will
                 * be implemented.
                 */
                if (m->box_flags & HCLR_BOX) {
                    av_bprintf(buf, "{\\2c&H%02x%02x%02x&}", m->c.hlit_color[2],
                                m->c.hlit_color[1], m->c.hlit_color[0]);
                } else {
                    av_bprintf(buf, "{\\1c&H000000&}{\\2c&HFFFFFF&}");
                }
            }
            if (text_pos == m->h.hlit_end) {
                if (m->box_flags & HCLR_BOX) {
                    av_bprintf(buf, "{\\2c&H000000&}");
                } else {
                    av_bprintf(buf, "{\\1c&HFFFFFF&}{\\2c&H000000&}");
                }
            }
        }

        len = get_utf8_length_at(text, text_end);
        if (len < 1) {
            av_log(avctx, AV_LOG_ERROR, "invalid UTF-8 byte in subtitle\n");
            len = 1;
        }
        for (i = 0; i < len; i++) {
            switch (*text) {
            case '\r':
                break;
            case '\n':
                av_bprintf(buf, "\\N");
                break;
            default:
                av_bprint_chars(buf, *text, 1);
                break;
            }
            text++;
        }
        text_pos++;
    }

    return 0;
}