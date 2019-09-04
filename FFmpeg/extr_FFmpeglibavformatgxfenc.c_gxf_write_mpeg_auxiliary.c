#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_7__ {TYPE_1__* codecpar; TYPE_2__* priv_data; } ;
struct TYPE_6__ {int iframes; int p_per_gop; int pframes; int b_per_i_or_p; int bframes; int first_gop_closed; } ;
struct TYPE_5__ {int height; scalar_t__ format; scalar_t__ bit_rate; } ;
typedef  TYPE_2__ GXFStreamContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 int TRACK_MPG_AUX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int snprintf (char*,int,char*,float,int,int,int,int,int,int) ; 

__attribute__((used)) static int gxf_write_mpeg_auxiliary(AVIOContext *pb, AVStream *st)
{
    GXFStreamContext *sc = st->priv_data;
    char buffer[1024];
    int size, starting_line;

    if (sc->iframes) {
        sc->p_per_gop = sc->pframes / sc->iframes;
        if (sc->pframes % sc->iframes)
            sc->p_per_gop++;
        if (sc->pframes) {
            sc->b_per_i_or_p = sc->bframes / sc->pframes;
            if (sc->bframes % sc->pframes)
                sc->b_per_i_or_p++;
        }
        if (sc->p_per_gop > 9)
            sc->p_per_gop = 9; /* ensure value won't take more than one char */
        if (sc->b_per_i_or_p > 9)
            sc->b_per_i_or_p = 9; /* ensure value won't take more than one char */
    }
    if (st->codecpar->height == 512 || st->codecpar->height == 608)
        starting_line = 7; // VBI
    else if (st->codecpar->height == 480)
        starting_line = 20;
    else
        starting_line = 23; // default PAL

    size = snprintf(buffer, sizeof(buffer), "Ver 1\nBr %.6f\nIpg 1\nPpi %d\nBpiop %d\n"
                    "Pix 0\nCf %d\nCg %d\nSl %d\nnl16 %d\nVi 1\nf1 1\n",
                    (float)st->codecpar->bit_rate, sc->p_per_gop, sc->b_per_i_or_p,
                    st->codecpar->format == AV_PIX_FMT_YUV422P ? 2 : 1, sc->first_gop_closed == 1,
                    starting_line, (st->codecpar->height + 15) / 16);
    av_assert0(size < sizeof(buffer));
    avio_w8(pb, TRACK_MPG_AUX);
    avio_w8(pb, size + 1);
    avio_write(pb, (uint8_t *)buffer, size + 1);
    return size + 3;
}