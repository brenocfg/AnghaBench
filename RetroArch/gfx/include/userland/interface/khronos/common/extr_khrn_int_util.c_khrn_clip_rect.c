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
 int /*<<< orphan*/  khrn_clip_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void khrn_clip_rect(
   int32_t *x0, int32_t *y0, int32_t *w0, int32_t *h0,
   int32_t x1, int32_t y1, int32_t w1, int32_t h1)
{
   khrn_clip_range(x0, w0, x1, w1);
   khrn_clip_range(y0, h0, y1, h1);
}