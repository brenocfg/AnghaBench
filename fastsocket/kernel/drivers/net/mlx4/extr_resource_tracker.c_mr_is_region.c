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
struct mlx4_mpt_entry {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int MLX4_MPT_FLAG_REGION ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mr_is_region(struct mlx4_mpt_entry *mpt)
{
	return be32_to_cpu(mpt->flags) & MLX4_MPT_FLAG_REGION;
}