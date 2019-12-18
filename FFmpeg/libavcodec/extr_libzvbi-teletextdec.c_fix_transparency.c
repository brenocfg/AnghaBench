#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int columns; TYPE_2__* text; } ;
typedef  TYPE_1__ vbi_page ;
struct TYPE_9__ {int opacity; int /*<<< orphan*/  background; } ;
typedef  TYPE_2__ vbi_char ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int opacity; int /*<<< orphan*/  transparent_bg; } ;
typedef  TYPE_3__ TeletextContext ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_4__ AVSubtitleRect ;

/* Variables and functions */
 int BITMAP_CHAR_HEIGHT ; 
 int BITMAP_CHAR_WIDTH ; 
 int /*<<< orphan*/  VBI_NB_COLORS ; 
#define  VBI_OPAQUE 131 
#define  VBI_SEMI_TRANSPARENT 130 
 int /*<<< orphan*/  VBI_TRANSPARENT_BLACK ; 
#define  VBI_TRANSPARENT_FULL 129 
#define  VBI_TRANSPARENT_SPACE 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fix_transparency(TeletextContext *ctx, AVSubtitleRect *sub_rect, vbi_page *page,
                             int chop_top, int resx, int resy)
{
    int iy;

    // Hack for transparency, inspired by VLC code...
    for (iy = 0; iy < resy; iy++) {
        uint8_t *pixel = sub_rect->data[0] + iy * sub_rect->linesize[0];
        vbi_char *vc = page->text + (iy / BITMAP_CHAR_HEIGHT + chop_top) * page->columns;
        vbi_char *vcnext = vc + page->columns;
        for (; vc < vcnext; vc++) {
            uint8_t *pixelnext = pixel + BITMAP_CHAR_WIDTH;
            switch (vc->opacity) {
                case VBI_TRANSPARENT_SPACE:
                    memset(pixel, VBI_TRANSPARENT_BLACK, BITMAP_CHAR_WIDTH);
                    break;
                case VBI_OPAQUE:
                    if (!ctx->transparent_bg)
                        break;
                case VBI_SEMI_TRANSPARENT:
                    if (ctx->opacity > 0) {
                        if (ctx->opacity < 255)
                            for(; pixel < pixelnext; pixel++)
                                if (*pixel == vc->background)
                                    *pixel += VBI_NB_COLORS;
                        break;
                    }
                case VBI_TRANSPARENT_FULL:
                    for(; pixel < pixelnext; pixel++)
                        if (*pixel == vc->background)
                            *pixel = VBI_TRANSPARENT_BLACK;
                    break;
            }
            pixel = pixelnext;
        }
    }
}