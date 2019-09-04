#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTERFLY1 (int,int) ; 
 int /*<<< orphan*/  BUTTERFLY2 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BUTTERFLYA (int,int) ; 
 scalar_t__ FFABS (int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static int hadamard8_intra8x8_c(MpegEncContext *s, uint8_t *src,
                                uint8_t *dummy, ptrdiff_t stride, int h)
{
    int i, temp[64], sum = 0;

    av_assert2(h == 8);

    for (i = 0; i < 8; i++) {
        // FIXME: try pointer walks
        BUTTERFLY2(temp[8 * i + 0], temp[8 * i + 1],
                   src[stride * i + 0], src[stride * i + 1]);
        BUTTERFLY2(temp[8 * i + 2], temp[8 * i + 3],
                   src[stride * i + 2], src[stride * i + 3]);
        BUTTERFLY2(temp[8 * i + 4], temp[8 * i + 5],
                   src[stride * i + 4], src[stride * i + 5]);
        BUTTERFLY2(temp[8 * i + 6], temp[8 * i + 7],
                   src[stride * i + 6], src[stride * i + 7]);

        BUTTERFLY1(temp[8 * i + 0], temp[8 * i + 2]);
        BUTTERFLY1(temp[8 * i + 1], temp[8 * i + 3]);
        BUTTERFLY1(temp[8 * i + 4], temp[8 * i + 6]);
        BUTTERFLY1(temp[8 * i + 5], temp[8 * i + 7]);

        BUTTERFLY1(temp[8 * i + 0], temp[8 * i + 4]);
        BUTTERFLY1(temp[8 * i + 1], temp[8 * i + 5]);
        BUTTERFLY1(temp[8 * i + 2], temp[8 * i + 6]);
        BUTTERFLY1(temp[8 * i + 3], temp[8 * i + 7]);
    }

    for (i = 0; i < 8; i++) {
        BUTTERFLY1(temp[8 * 0 + i], temp[8 * 1 + i]);
        BUTTERFLY1(temp[8 * 2 + i], temp[8 * 3 + i]);
        BUTTERFLY1(temp[8 * 4 + i], temp[8 * 5 + i]);
        BUTTERFLY1(temp[8 * 6 + i], temp[8 * 7 + i]);

        BUTTERFLY1(temp[8 * 0 + i], temp[8 * 2 + i]);
        BUTTERFLY1(temp[8 * 1 + i], temp[8 * 3 + i]);
        BUTTERFLY1(temp[8 * 4 + i], temp[8 * 6 + i]);
        BUTTERFLY1(temp[8 * 5 + i], temp[8 * 7 + i]);

        sum +=
            BUTTERFLYA(temp[8 * 0 + i], temp[8 * 4 + i])
            + BUTTERFLYA(temp[8 * 1 + i], temp[8 * 5 + i])
            + BUTTERFLYA(temp[8 * 2 + i], temp[8 * 6 + i])
            + BUTTERFLYA(temp[8 * 3 + i], temp[8 * 7 + i]);
    }

    sum -= FFABS(temp[8 * 0] + temp[8 * 4]); // -mean

    return sum;
}