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
typedef  enum mlx4_mw_type { ____Placeholder_mlx4_mw_type } mlx4_mw_type ;
typedef  enum ib_mw_type { ____Placeholder_ib_mw_type } ib_mw_type ;

/* Variables and functions */
#define  IB_MW_TYPE_1 129 
#define  IB_MW_TYPE_2 128 
 int MLX4_MW_TYPE_1 ; 
 int MLX4_MW_TYPE_2 ; 

__attribute__((used)) static enum mlx4_mw_type to_mlx4_type(enum ib_mw_type type)
{
	switch (type) {
	case IB_MW_TYPE_1:	return MLX4_MW_TYPE_1;
	case IB_MW_TYPE_2:	return MLX4_MW_TYPE_2;
	default:		return -1;
	}
}