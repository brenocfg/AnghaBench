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
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int dx2_decode_slice_5x5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dx2_decode_slice_555(GetBitContext *gb, AVFrame *frame,
                                int line, int left, uint8_t lru[3][8])
{
    return dx2_decode_slice_5x5(gb, frame, line, left, lru, 0);
}