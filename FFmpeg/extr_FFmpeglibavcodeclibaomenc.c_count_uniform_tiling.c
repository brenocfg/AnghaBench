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

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int count_uniform_tiling(int dim, int sb_size, int tiles_log2)
{
    int sb_dim   = (dim + sb_size - 1) / sb_size;
    int tile_dim = (sb_dim + (1 << tiles_log2) - 1) >> tiles_log2;
    av_assert0(tile_dim > 0);
    return (sb_dim + tile_dim - 1) / tile_dim;
}