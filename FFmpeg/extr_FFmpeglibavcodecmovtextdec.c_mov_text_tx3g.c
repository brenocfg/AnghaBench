#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int8_t ;
struct TYPE_16__ {int fontID; int /*<<< orphan*/  font; } ;
struct TYPE_15__ {char* font; void* fontID; } ;
struct TYPE_14__ {int extradata_size; int /*<<< orphan*/ * extradata; } ;
struct TYPE_11__ {int bold; int italic; int underline; int /*<<< orphan*/  font; void* color; int /*<<< orphan*/  fontsize; void* back_color; int /*<<< orphan*/  alignment; } ;
struct TYPE_13__ {int ftab_entries; TYPE_9__** ftab; TYPE_1__ d; TYPE_8__* ftab_temp; scalar_t__ count_f; } ;
struct TYPE_12__ {int style_flag; } ;
typedef  TYPE_2__ StyleBox ;
typedef  TYPE_3__ MovTextContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_RB16 (int /*<<< orphan*/ *) ; 
 void* AV_RB24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BOTTOM_CENTER ; 
 int /*<<< orphan*/  BOTTOM_LEFT ; 
 int /*<<< orphan*/  BOTTOM_RIGHT ; 
 int BOX_SIZE_INITIAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MIDDLE_CENTER ; 
 int /*<<< orphan*/  MIDDLE_LEFT ; 
 int /*<<< orphan*/  MIDDLE_RIGHT ; 
 int STYLE_FLAG_BOLD ; 
 int STYLE_FLAG_ITALIC ; 
 int STYLE_FLAG_UNDERLINE ; 
 int /*<<< orphan*/  TOP_CENTER ; 
 int /*<<< orphan*/  TOP_LEFT ; 
 int /*<<< orphan*/  TOP_RIGHT ; 
 int /*<<< orphan*/  av_dynarray_add (TYPE_9__***,scalar_t__*,TYPE_8__*) ; 
 char* av_malloc (int) ; 
 TYPE_8__* av_mallocz (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mov_text_cleanup_ftab (TYPE_3__*) ; 

__attribute__((used)) static int mov_text_tx3g(AVCodecContext *avctx, MovTextContext *m)
{
    uint8_t *tx3g_ptr = avctx->extradata;
    int i, box_size, font_length;
    int8_t v_align, h_align;
    int style_fontID;
    StyleBox s_default;

    m->count_f = 0;
    m->ftab_entries = 0;
    box_size = BOX_SIZE_INITIAL; /* Size till ftab_entries */
    if (avctx->extradata_size < box_size)
        return -1;

    // Display Flags
    tx3g_ptr += 4;
    // Alignment
    h_align = *tx3g_ptr++;
    v_align = *tx3g_ptr++;
    if (h_align == 0) {
        if (v_align == 0)
            m->d.alignment = TOP_LEFT;
        if (v_align == 1)
            m->d.alignment = MIDDLE_LEFT;
        if (v_align == -1)
            m->d.alignment = BOTTOM_LEFT;
    }
    if (h_align == 1) {
        if (v_align == 0)
            m->d.alignment = TOP_CENTER;
        if (v_align == 1)
            m->d.alignment = MIDDLE_CENTER;
        if (v_align == -1)
            m->d.alignment = BOTTOM_CENTER;
    }
    if (h_align == -1) {
        if (v_align == 0)
            m->d.alignment = TOP_RIGHT;
        if (v_align == 1)
            m->d.alignment = MIDDLE_RIGHT;
        if (v_align == -1)
            m->d.alignment = BOTTOM_RIGHT;
    }
    // Background Color
    m->d.back_color = AV_RB24(tx3g_ptr);
    tx3g_ptr += 4;
    // BoxRecord
    tx3g_ptr += 8;
    // StyleRecord
    tx3g_ptr += 4;
    // fontID
    style_fontID = AV_RB16(tx3g_ptr);
    tx3g_ptr += 2;
    // face-style-flags
    s_default.style_flag = *tx3g_ptr++;
    m->d.bold = s_default.style_flag & STYLE_FLAG_BOLD;
    m->d.italic = s_default.style_flag & STYLE_FLAG_ITALIC;
    m->d.underline = s_default.style_flag & STYLE_FLAG_UNDERLINE;
    // fontsize
    m->d.fontsize = *tx3g_ptr++;
    // Primary color
    m->d.color = AV_RB24(tx3g_ptr);
    tx3g_ptr += 4;
    // FontRecord
    // FontRecord Size
    tx3g_ptr += 4;
    // ftab
    tx3g_ptr += 4;

    m->ftab_entries = AV_RB16(tx3g_ptr);
    tx3g_ptr += 2;

    for (i = 0; i < m->ftab_entries; i++) {

        box_size += 3;
        if (avctx->extradata_size < box_size) {
            mov_text_cleanup_ftab(m);
            m->ftab_entries = 0;
            return -1;
        }
        m->ftab_temp = av_mallocz(sizeof(*m->ftab_temp));
        if (!m->ftab_temp) {
            mov_text_cleanup_ftab(m);
            return AVERROR(ENOMEM);
        }
        m->ftab_temp->fontID = AV_RB16(tx3g_ptr);
        tx3g_ptr += 2;
        font_length = *tx3g_ptr++;

        box_size = box_size + font_length;
        if (avctx->extradata_size < box_size) {
            mov_text_cleanup_ftab(m);
            m->ftab_entries = 0;
            return -1;
        }
        m->ftab_temp->font = av_malloc(font_length + 1);
        if (!m->ftab_temp->font) {
            mov_text_cleanup_ftab(m);
            return AVERROR(ENOMEM);
        }
        memcpy(m->ftab_temp->font, tx3g_ptr, font_length);
        m->ftab_temp->font[font_length] = '\0';
        av_dynarray_add(&m->ftab, &m->count_f, m->ftab_temp);
        if (!m->ftab) {
            mov_text_cleanup_ftab(m);
            return AVERROR(ENOMEM);
        }
        m->ftab_temp = NULL;
        tx3g_ptr = tx3g_ptr + font_length;
    }
    for (i = 0; i < m->ftab_entries; i++) {
        if (style_fontID == m->ftab[i]->fontID)
            m->d.font = m->ftab[i]->font;
    }
    return 0;
}