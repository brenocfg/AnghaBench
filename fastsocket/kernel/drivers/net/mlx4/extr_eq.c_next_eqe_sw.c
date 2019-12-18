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
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_eqe {int owner; } ;
struct mlx4_eq {int cons_index; int nent; } ;

/* Variables and functions */
 struct mlx4_eqe* get_eqe (struct mlx4_eq*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx4_eqe *next_eqe_sw(struct mlx4_eq *eq, u8 eqe_factor)
{
	struct mlx4_eqe *eqe = get_eqe(eq, eq->cons_index, eqe_factor);
	return !!(eqe->owner & 0x80) ^ !!(eq->cons_index & eq->nent) ? NULL : eqe;
}