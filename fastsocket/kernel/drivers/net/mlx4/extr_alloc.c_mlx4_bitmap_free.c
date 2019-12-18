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
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_bitmap_free_range (struct mlx4_bitmap*,int /*<<< orphan*/ ,int) ; 

void mlx4_bitmap_free(struct mlx4_bitmap *bitmap, u32 obj)
{
	mlx4_bitmap_free_range(bitmap, obj, 1);
}