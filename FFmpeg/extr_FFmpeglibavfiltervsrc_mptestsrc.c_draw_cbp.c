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

/* Variables and functions */
 int /*<<< orphan*/  draw_basis (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void draw_cbp(uint8_t *dst[3], int dst_linesize[3], int cbp, int amp, int dc)
{
    if (cbp&1)  draw_basis(dst[0]                    , dst_linesize[0], amp, 1, dc);
    if (cbp&2)  draw_basis(dst[0]+8                  , dst_linesize[0], amp, 1, dc);
    if (cbp&4)  draw_basis(dst[0]+  8*dst_linesize[0], dst_linesize[0], amp, 1, dc);
    if (cbp&8)  draw_basis(dst[0]+8+8*dst_linesize[0], dst_linesize[0], amp, 1, dc);
    if (cbp&16) draw_basis(dst[1]                    , dst_linesize[1], amp, 1, dc);
    if (cbp&32) draw_basis(dst[2]                    , dst_linesize[2], amp, 1, dc);
}