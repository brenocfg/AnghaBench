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
struct dio200_subdev_8254 {int* gate_src; int /*<<< orphan*/  has_clk_gat_sce; } ;

/* Variables and functions */

__attribute__((used)) static int
dio200_get_gate_src(struct dio200_subdev_8254 *subpriv,
		    unsigned int counter_number)
{
	if (!subpriv->has_clk_gat_sce)
		return -1;
	if (counter_number > 2)
		return -1;

	return subpriv->gate_src[counter_number];
}