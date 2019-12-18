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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ff_ivi_put_dc_pixel_8x8(const int32_t *in, int16_t *out, ptrdiff_t pitch,
                             int blk_size)
{
    int     y;

    out[0] = in[0];
    memset(out + 1, 0, 7*sizeof(out[0]));
    out += pitch;

    for (y = 1; y < 8; out += pitch, y++)
        memset(out, 0, 8*sizeof(out[0]));
}