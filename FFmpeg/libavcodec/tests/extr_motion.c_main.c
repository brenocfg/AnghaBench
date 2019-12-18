#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mmxctx ;
typedef  int /*<<< orphan*/  cctx ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** pix_abs; } ;
typedef  TYPE_1__ MECmpContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_FLAG_BITEXACT ; 
 int AV_CPU_FLAG_MMX ; 
 int AV_CPU_FLAG_MMXEXT ; 
 scalar_t__ HAVE_MMXEXT ; 
 int /*<<< orphan*/  av_force_cpu_flags (int) ; 
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 TYPE_2__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_me_cmp_init (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  test_motion (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
    AVCodecContext *ctx;
    int c;
    MECmpContext cctx, mmxctx;
    int flags[2] = { AV_CPU_FLAG_MMX, AV_CPU_FLAG_MMXEXT };
    int flags_size = HAVE_MMXEXT ? 2 : 1;

    if (argc > 1) {
        help();
        return 1;
    }

    printf("ffmpeg motion test\n");

    ctx = avcodec_alloc_context3(NULL);
    ctx->flags |= AV_CODEC_FLAG_BITEXACT;
    av_force_cpu_flags(0);
    memset(&cctx, 0, sizeof(cctx));
    ff_me_cmp_init(&cctx, ctx);
    for (c = 0; c < flags_size; c++) {
        int x;
        av_force_cpu_flags(flags[c]);
        memset(&mmxctx, 0, sizeof(mmxctx));
        ff_me_cmp_init(&mmxctx, ctx);

        for (x = 0; x < 2; x++) {
            printf("%s for %dx%d pixels\n", c ? "mmx2" : "mmx",
                   x ? 8 : 16, x ? 8 : 16);
            test_motion("mmx",     mmxctx.pix_abs[x][0], cctx.pix_abs[x][0]);
            test_motion("mmx_x2",  mmxctx.pix_abs[x][1], cctx.pix_abs[x][1]);
            test_motion("mmx_y2",  mmxctx.pix_abs[x][2], cctx.pix_abs[x][2]);
            test_motion("mmx_xy2", mmxctx.pix_abs[x][3], cctx.pix_abs[x][3]);
        }
    }
    av_free(ctx);

    return 0;
}