#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ ShowCQTContext ;
typedef  scalar_t__ FcResult ;
typedef  int /*<<< orphan*/  FcPattern ;
typedef  int /*<<< orphan*/  FcConfig ;
typedef  int /*<<< orphan*/  FcChar8 ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FC_FILE ; 
 int /*<<< orphan*/  FcConfigDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcConfigSubstitute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FcDefaultSubstitute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FcFontMatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * FcInitLoadConfigAndFonts () ; 
 int /*<<< orphan*/  FcMatchPattern ; 
 int /*<<< orphan*/ * FcNameParse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcPatternDestroy (int /*<<< orphan*/ *) ; 
 scalar_t__ FcPatternGetString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FcResultMatch ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int render_freetype (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int render_fontconfig(ShowCQTContext *s, AVFrame *tmp, char* font)
{
#if CONFIG_LIBFONTCONFIG
    FcConfig *fontconfig;
    FcPattern *pat, *best;
    FcResult result = FcResultMatch;
    char *filename;
    int i, ret;

    if (!font)
        return AVERROR(EINVAL);

    for (i = 0; font[i]; i++) {
        if (font[i] == '|')
            font[i] = ':';
    }

    if (!(fontconfig = FcInitLoadConfigAndFonts())) {
        av_log(s->ctx, AV_LOG_ERROR, "impossible to init fontconfig.\n");
        return AVERROR_UNKNOWN;
    }

    if (!(pat = FcNameParse((uint8_t *)font))) {
        av_log(s->ctx, AV_LOG_ERROR, "could not parse fontconfig pat.\n");
        FcConfigDestroy(fontconfig);
        return AVERROR(EINVAL);
    }

    FcDefaultSubstitute(pat);

    if (!FcConfigSubstitute(fontconfig, pat, FcMatchPattern)) {
        av_log(s->ctx, AV_LOG_ERROR, "could not substitue fontconfig options.\n");
        FcPatternDestroy(pat);
        FcConfigDestroy(fontconfig);
        return AVERROR(ENOMEM);
    }

    best = FcFontMatch(fontconfig, pat, &result);
    FcPatternDestroy(pat);

    ret = AVERROR(EINVAL);
    if (!best || result != FcResultMatch) {
        av_log(s->ctx, AV_LOG_ERROR, "cannot find a valid font for %s.\n", font);
        goto fail;
    }

    if (FcPatternGetString(best, FC_FILE, 0, (FcChar8 **)&filename) != FcResultMatch) {
        av_log(s->ctx, AV_LOG_ERROR, "no file path for %s\n", font);
        goto fail;
    }

    ret = render_freetype(s, tmp, filename);

fail:
    FcPatternDestroy(best);
    FcConfigDestroy(fontconfig);
    return ret;
#else
    if (font)
        av_log(s->ctx, AV_LOG_WARNING, "fontconfig is not available, ignoring font option.\n");
    return AVERROR(EINVAL);
#endif
}