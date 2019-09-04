#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct AVTreeNode {int advance; struct AVTreeNode* glyph; int /*<<< orphan*/  bbox; int /*<<< orphan*/  bitmap_top; int /*<<< orphan*/  bitmap_left; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  border_bitmap; struct AVTreeNode* border_glyph; int /*<<< orphan*/  fontsize; int /*<<< orphan*/  code; } ;
struct TYPE_8__ {int x; } ;
struct TYPE_13__ {TYPE_1__ advance; } ;
struct TYPE_12__ {TYPE_7__* glyph; } ;
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  glyphs; TYPE_6__* face; int /*<<< orphan*/  stroker; scalar_t__ borderw; int /*<<< orphan*/  fontsize; int /*<<< orphan*/  ft_load_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  bitmap; } ;
typedef  struct AVTreeNode Glyph ;
typedef  TYPE_2__* FT_BitmapGlyph ;
typedef  TYPE_3__ DrawTextContext ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FT_Get_Glyph (TYPE_7__*,struct AVTreeNode**) ; 
 int /*<<< orphan*/  FT_Glyph_Get_CBox (struct AVTreeNode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FT_Glyph_StrokeBorder (struct AVTreeNode**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Glyph_To_Bitmap (struct AVTreeNode**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FT_Load_Char (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_RENDER_MODE_NORMAL ; 
 int /*<<< orphan*/  av_freep (struct AVTreeNode**) ; 
 struct AVTreeNode* av_mallocz (int) ; 
 int /*<<< orphan*/  av_tree_insert (int /*<<< orphan*/ *,struct AVTreeNode*,int /*<<< orphan*/ ,struct AVTreeNode**) ; 
 struct AVTreeNode* av_tree_node_alloc () ; 
 int /*<<< orphan*/  ft_glyph_bbox_pixels ; 
 int /*<<< orphan*/  glyph_cmp ; 

__attribute__((used)) static int load_glyph(AVFilterContext *ctx, Glyph **glyph_ptr, uint32_t code)
{
    DrawTextContext *s = ctx->priv;
    FT_BitmapGlyph bitmapglyph;
    Glyph *glyph;
    struct AVTreeNode *node = NULL;
    int ret;

    /* load glyph into s->face->glyph */
    if (FT_Load_Char(s->face, code, s->ft_load_flags))
        return AVERROR(EINVAL);

    glyph = av_mallocz(sizeof(*glyph));
    if (!glyph) {
        ret = AVERROR(ENOMEM);
        goto error;
    }
    glyph->code  = code;
    glyph->fontsize = s->fontsize;

    if (FT_Get_Glyph(s->face->glyph, &glyph->glyph)) {
        ret = AVERROR(EINVAL);
        goto error;
    }
    if (s->borderw) {
        glyph->border_glyph = glyph->glyph;
        if (FT_Glyph_StrokeBorder(&glyph->border_glyph, s->stroker, 0, 0) ||
            FT_Glyph_To_Bitmap(&glyph->border_glyph, FT_RENDER_MODE_NORMAL, 0, 1)) {
            ret = AVERROR_EXTERNAL;
            goto error;
        }
        bitmapglyph = (FT_BitmapGlyph) glyph->border_glyph;
        glyph->border_bitmap = bitmapglyph->bitmap;
    }
    if (FT_Glyph_To_Bitmap(&glyph->glyph, FT_RENDER_MODE_NORMAL, 0, 1)) {
        ret = AVERROR_EXTERNAL;
        goto error;
    }
    bitmapglyph = (FT_BitmapGlyph) glyph->glyph;

    glyph->bitmap      = bitmapglyph->bitmap;
    glyph->bitmap_left = bitmapglyph->left;
    glyph->bitmap_top  = bitmapglyph->top;
    glyph->advance     = s->face->glyph->advance.x >> 6;

    /* measure text height to calculate text_height (or the maximum text height) */
    FT_Glyph_Get_CBox(glyph->glyph, ft_glyph_bbox_pixels, &glyph->bbox);

    /* cache the newly created glyph */
    if (!(node = av_tree_node_alloc())) {
        ret = AVERROR(ENOMEM);
        goto error;
    }
    av_tree_insert(&s->glyphs, glyph, glyph_cmp, &node);

    if (glyph_ptr)
        *glyph_ptr = glyph;
    return 0;

error:
    if (glyph)
        av_freep(&glyph->glyph);

    av_freep(&glyph);
    av_freep(&node);
    return ret;
}