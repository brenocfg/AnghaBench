#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * idct_permutation; } ;
struct TYPE_4__ {TYPE_3__ idsp; int /*<<< orphan*/ * scan; } ;
typedef  TYPE_1__ RTJpegContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_idctdsp_init (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int* ff_zigzag_direct ; 

void ff_rtjpeg_init(RTJpegContext *c, AVCodecContext *avctx)
{
    int i;

    ff_idctdsp_init(&c->idsp, avctx);

    for (i = 0; i < 64; i++) {
        int z = ff_zigzag_direct[i];
        z = ((z << 3) | (z >> 3)) & 63; // rtjpeg uses a transposed variant

        // permute the scan and quantization tables for the chosen idct
        c->scan[i] = c->idsp.idct_permutation[z];
    }
}