#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_6__ {int format; } ;
struct TYPE_7__ {TYPE_1__ out; } ;
typedef  TYPE_2__ Stereo3DContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
#define  ANAGLYPH_GM_COLOR 141 
#define  ANAGLYPH_GM_DUBOIS 140 
#define  ANAGLYPH_GM_GRAY 139 
#define  ANAGLYPH_GM_HALF 138 
#define  ANAGLYPH_RB_GRAY 137 
#define  ANAGLYPH_RC_COLOR 136 
#define  ANAGLYPH_RC_DUBOIS 135 
#define  ANAGLYPH_RC_GRAY 134 
#define  ANAGLYPH_RC_HALF 133 
#define  ANAGLYPH_RG_GRAY 132 
#define  ANAGLYPH_YB_COLOR 131 
#define  ANAGLYPH_YB_DUBOIS 130 
#define  ANAGLYPH_YB_GRAY 129 
#define  ANAGLYPH_YB_HALF 128 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int* anaglyph_pix_fmts ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int* other_pix_fmts ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    Stereo3DContext *s = ctx->priv;
    const enum AVPixelFormat *pix_fmts;
    AVFilterFormats *fmts_list;

    switch (s->out.format) {
    case ANAGLYPH_GM_COLOR:
    case ANAGLYPH_GM_DUBOIS:
    case ANAGLYPH_GM_GRAY:
    case ANAGLYPH_GM_HALF:
    case ANAGLYPH_RB_GRAY:
    case ANAGLYPH_RC_COLOR:
    case ANAGLYPH_RC_DUBOIS:
    case ANAGLYPH_RC_GRAY:
    case ANAGLYPH_RC_HALF:
    case ANAGLYPH_RG_GRAY:
    case ANAGLYPH_YB_COLOR:
    case ANAGLYPH_YB_DUBOIS:
    case ANAGLYPH_YB_GRAY:
    case ANAGLYPH_YB_HALF:
        pix_fmts = anaglyph_pix_fmts;
        break;
    default:
        pix_fmts = other_pix_fmts;
    }

    fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}