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
typedef  int uint8_t ;
struct TYPE_3__ {int width; int* linesize; int** data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int decode_sym (int /*<<< orphan*/ *,int*) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dx2_decode_slice_444(GetBitContext *gb, AVFrame *frame,
                                int line, int left,
                                uint8_t lru[3][8])
{
    int x, y;

    int width   = frame->width;

    int ystride = frame->linesize[0];
    int ustride = frame->linesize[1];
    int vstride = frame->linesize[2];

    uint8_t *Y  = frame->data[0] + ystride * line;
    uint8_t *U  = frame->data[1] + ustride * line;
    uint8_t *V  = frame->data[2] + vstride * line;

    for (y = 0; y < left && get_bits_left(gb) > 6 * width; y++) {
        for (x = 0; x < width; x++) {
            Y[x] = decode_sym(gb, lru[0]);
            U[x] = decode_sym(gb, lru[1]) ^ 0x80;
            V[x] = decode_sym(gb, lru[2]) ^ 0x80;
        }

        Y += ystride;
        U += ustride;
        V += vstride;
    }

    return y;
}