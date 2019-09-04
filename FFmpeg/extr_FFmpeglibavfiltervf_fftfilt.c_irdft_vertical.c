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
struct TYPE_3__ {int* rdft_hlen; int* rdft_vlen; int /*<<< orphan*/ ** rdft_vdata; int /*<<< orphan*/ ** rdft_hdata; int /*<<< orphan*/ * ivrdft; } ;
typedef  TYPE_1__ FFTFILTContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void irdft_vertical(FFTFILTContext *s, int h, int plane)
{
    int i, j;

    for (i = 0; i < s->rdft_hlen[plane]; i++)
        av_rdft_calc(s->ivrdft[plane], s->rdft_vdata[plane] + i * s->rdft_vlen[plane]);

    for (i = 0; i < s->rdft_hlen[plane]; i++)
        for (j = 0; j < h; j++)
            s->rdft_hdata[plane][j * s->rdft_hlen[plane] + i] =
            s->rdft_vdata[plane][i * s->rdft_vlen[plane] + j];
}