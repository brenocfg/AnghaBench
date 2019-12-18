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
typedef  int uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ VLC ;
struct TYPE_8__ {TYPE_1__* avctx; } ;
struct TYPE_6__ {int width; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ CLLCContext ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_VLC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_BITS ; 
 int /*<<< orphan*/  VLC_DEPTH ; 
 int /*<<< orphan*/  bits ; 

__attribute__((used)) static int read_argb_line(CLLCContext *ctx, GetBitContext *gb, int *top_left,
                          VLC *vlc, uint8_t *outbuf)
{
    uint8_t *dst;
    int pred[4];
    int code;
    int i;

    OPEN_READER(bits, gb);

    dst     = outbuf;
    pred[0] = top_left[0];
    pred[1] = top_left[1];
    pred[2] = top_left[2];
    pred[3] = top_left[3];

    for (i = 0; i < ctx->avctx->width; i++) {
        /* Always get the alpha component */
        UPDATE_CACHE(bits, gb);
        GET_VLC(code, bits, gb, vlc[0].table, VLC_BITS, VLC_DEPTH);

        pred[0] += code;
        dst[0]   = pred[0];

        /* Skip the components if they are  entirely transparent */
        if (dst[0]) {
            /* Red */
            UPDATE_CACHE(bits, gb);
            GET_VLC(code, bits, gb, vlc[1].table, VLC_BITS, VLC_DEPTH);

            pred[1] += code;
            dst[1]   = pred[1];

            /* Green */
            UPDATE_CACHE(bits, gb);
            GET_VLC(code, bits, gb, vlc[2].table, VLC_BITS, VLC_DEPTH);

            pred[2] += code;
            dst[2]   = pred[2];

            /* Blue */
            UPDATE_CACHE(bits, gb);
            GET_VLC(code, bits, gb, vlc[3].table, VLC_BITS, VLC_DEPTH);

            pred[3] += code;
            dst[3]   = pred[3];
        } else {
            dst[1] = 0;
            dst[2] = 0;
            dst[3] = 0;
        }

        dst += 4;
    }

    CLOSE_READER(bits, gb);

    top_left[0]  = outbuf[0];

    /* Only stash components if they are not transparent */
    if (top_left[0]) {
        top_left[1] = outbuf[1];
        top_left[2] = outbuf[2];
        top_left[3] = outbuf[3];
    }

    return 0;
}