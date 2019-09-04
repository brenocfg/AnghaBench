#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  fontfile; int /*<<< orphan*/  face; int /*<<< orphan*/  library; } ;
typedef  TYPE_1__ DrawTextContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FT_ERRMSG (int) ; 
 int FT_New_Face (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_font_file(AVFilterContext *ctx, const char *path, int index)
{
    DrawTextContext *s = ctx->priv;
    int err;

    err = FT_New_Face(s->library, path, index, &s->face);
    if (err) {
#if !CONFIG_LIBFONTCONFIG
        av_log(ctx, AV_LOG_ERROR, "Could not load font \"%s\": %s\n",
               s->fontfile, FT_ERRMSG(err));
#endif
        return AVERROR(EINVAL);
    }
    return 0;
}