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
typedef  int /*<<< orphan*/  VP9TileData ;

/* Variables and functions */
 int /*<<< orphan*/  intra_recon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ff_vp9_intra_recon_16bpp(VP9TileData *td, ptrdiff_t y_off, ptrdiff_t uv_off)
{
    intra_recon(td, y_off, uv_off, 2);
}