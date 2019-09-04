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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ ShowCQTContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int render_freetype(ShowCQTContext *s, AVFrame *tmp, char *fontfile)
{
#if CONFIG_LIBFREETYPE
    const char *str = "EF G A BC D ";
    uint8_t *data = tmp->data[0];
    int linesize = tmp->linesize[0];
    FT_Library lib = NULL;
    FT_Face face = NULL;
    int font_width = 16, font_height = 32;
    int font_repeat = font_width * 12;
    int linear_hori_advance = font_width * 65536;
    int non_monospace_warning = 0;
    int x;

    if (!fontfile)
        return AVERROR(EINVAL);

    if (FT_Init_FreeType(&lib))
        goto fail;

    if (FT_New_Face(lib, fontfile, 0, &face))
        goto fail;

    if (FT_Set_Char_Size(face, 16*64, 0, 0, 0))
        goto fail;

    if (FT_Load_Char(face, 'A', FT_LOAD_RENDER))
        goto fail;

    if (FT_Set_Char_Size(face, 16*64 * linear_hori_advance / face->glyph->linearHoriAdvance, 0, 0, 0))
        goto fail;

    for (x = 0; x < 12; x++) {
        int sx, sy, rx, bx, by, dx, dy;

        if (str[x] == ' ')
            continue;

        if (FT_Load_Char(face, str[x], FT_LOAD_RENDER))
            goto fail;

        if (face->glyph->advance.x != font_width*64 && !non_monospace_warning) {
            av_log(s->ctx, AV_LOG_WARNING, "font is not monospace.\n");
            non_monospace_warning = 1;
        }

        sy = font_height - 8 - face->glyph->bitmap_top;
        for (rx = 0; rx < 10; rx++) {
            sx = rx * font_repeat + x * font_width + face->glyph->bitmap_left;
            for (by = 0; by < face->glyph->bitmap.rows; by++) {
                dy = by + sy;
                if (dy < 0)
                    continue;
                if (dy >= font_height)
                    break;

                for (bx = 0; bx < face->glyph->bitmap.width; bx++) {
                    dx = bx + sx;
                    if (dx < 0)
                        continue;
                    if (dx >= 1920)
                        break;
                    data[dy*linesize+4*dx+3] = face->glyph->bitmap.buffer[by*face->glyph->bitmap.width+bx];
                }
            }
        }
    }

    FT_Done_Face(face);
    FT_Done_FreeType(lib);
    return 0;

fail:
    av_log(s->ctx, AV_LOG_WARNING, "error while loading freetype font.\n");
    FT_Done_Face(face);
    FT_Done_FreeType(lib);
    return AVERROR(EINVAL);
#else
    if (fontfile)
        av_log(s->ctx, AV_LOG_WARNING, "freetype is not available, ignoring fontfile option.\n");
    return AVERROR(EINVAL);
#endif
}