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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_clip_range2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void khrn_clip_rect2(
   int32_t *ax0, int32_t *ay0, int32_t *bx0, int32_t *by0, int32_t *w0, int32_t *h0,
   int32_t ax1, int32_t ay1, int32_t aw1, int32_t ah1,
   int32_t bx1, int32_t by1, int32_t bw1, int32_t bh1)
{
   khrn_clip_range2(ax0, bx0, w0, ax1, aw1, bx1, bw1);
   khrn_clip_range2(ay0, by0, h0, ay1, ah1, by1, bh1);
}