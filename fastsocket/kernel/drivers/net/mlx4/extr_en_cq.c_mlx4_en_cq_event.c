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
struct mlx4_cq {int dummy; } ;
typedef  enum mlx4_event { ____Placeholder_mlx4_event } mlx4_event ;

/* Variables and functions */

__attribute__((used)) static void mlx4_en_cq_event(struct mlx4_cq *cq, enum mlx4_event event)
{
	return;
}