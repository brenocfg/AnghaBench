#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ size_in_bits; } ;
struct TYPE_9__ {int divx_packed; int /*<<< orphan*/  avctx; } ;
struct TYPE_10__ {int divx_version; int divx_build; int lavc_build; int xvid_build; TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  TYPE_3__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 char get_bits (TYPE_3__*,int) ; 
 scalar_t__ get_bits_count (TYPE_3__*) ; 
 scalar_t__ show_bits (TYPE_3__*,int) ; 
 int sscanf (char*,char*,int*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int decode_user_data(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    MpegEncContext *s = &ctx->m;
    char buf[256];
    int i;
    int e;
    int ver = 0, build = 0, ver2 = 0, ver3 = 0;
    char last;

    for (i = 0; i < 255 && get_bits_count(gb) < gb->size_in_bits; i++) {
        if (show_bits(gb, 23) == 0)
            break;
        buf[i] = get_bits(gb, 8);
    }
    buf[i] = 0;

    /* divx detection */
    e = sscanf(buf, "DivX%dBuild%d%c", &ver, &build, &last);
    if (e < 2)
        e = sscanf(buf, "DivX%db%d%c", &ver, &build, &last);
    if (e >= 2) {
        ctx->divx_version = ver;
        ctx->divx_build   = build;
        s->divx_packed  = e == 3 && last == 'p';
    }

    /* libavcodec detection */
    e = sscanf(buf, "FFmpe%*[^b]b%d", &build) + 3;
    if (e != 4)
        e = sscanf(buf, "FFmpeg v%d.%d.%d / libavcodec build: %d", &ver, &ver2, &ver3, &build);
    if (e != 4) {
        e = sscanf(buf, "Lavc%d.%d.%d", &ver, &ver2, &ver3) + 1;
        if (e > 1) {
            if (ver > 0xFFU || ver2 > 0xFFU || ver3 > 0xFFU) {
                av_log(s->avctx, AV_LOG_WARNING,
                     "Unknown Lavc version string encountered, %d.%d.%d; "
                     "clamping sub-version values to 8-bits.\n",
                     ver, ver2, ver3);
            }
            build = ((ver & 0xFF) << 16) + ((ver2 & 0xFF) << 8) + (ver3 & 0xFF);
        }
    }
    if (e != 4) {
        if (strcmp(buf, "ffmpeg") == 0)
            ctx->lavc_build = 4600;
    }
    if (e == 4)
        ctx->lavc_build = build;

    /* Xvid detection */
    e = sscanf(buf, "XviD%d", &build);
    if (e == 1)
        ctx->xvid_build = build;

    return 0;
}