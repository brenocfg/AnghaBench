#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int row_step; } ;
struct TYPE_8__ {int* pheight; int* pixstep; int* linesize; TYPE_1__ out; } ;
typedef  TYPE_2__ Stereo3DContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB24 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_RB48 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_RN16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_RN32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_RN64 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WB48 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WN16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WN32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WN64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void interleave_cols_to_any(Stereo3DContext *s, int *out_off, int p, AVFrame *in, AVFrame *out, int d)
{
    int y, x;

    for (y = 0; y < s->pheight[p]; y++) {
        const uint8_t *src = (const uint8_t*)in->data[p] + y * in->linesize[p] + d * s->pixstep[p];
        uint8_t *dst = out->data[p] + out_off[p] + y * out->linesize[p] * s->out.row_step;

        switch (s->pixstep[p]) {
        case 1:
            for (x = 0; x < s->linesize[p]; x++)
                dst[x] = src[x * 2];
            break;
        case 2:
            for (x = 0; x < s->linesize[p]; x+=2)
                AV_WN16(&dst[x], AV_RN16(&src[x * 2]));
            break;
        case 3:
            for (x = 0; x < s->linesize[p]; x+=3)
                AV_WB24(&dst[x], AV_RB24(&src[x * 2]));
            break;
        case 4:
            for (x = 0; x < s->linesize[p]; x+=4)
                AV_WN32(&dst[x], AV_RN32(&src[x * 2]));
            break;
        case 6:
            for (x = 0; x < s->linesize[p]; x+=6)
                AV_WB48(&dst[x], AV_RB48(&src[x * 2]));
            break;
        case 8:
            for (x = 0; x < s->linesize[p]; x+=8)
                AV_WN64(&dst[x], AV_RN64(&src[x * 2]));
            break;
        }
    }
}