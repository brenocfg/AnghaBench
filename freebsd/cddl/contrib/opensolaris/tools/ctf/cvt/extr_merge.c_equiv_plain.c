#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  t_tdesc; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int /*<<< orphan*/  equiv_data_t ;

/* Variables and functions */
 int equiv_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
equiv_plain(tdesc_t *stdp, tdesc_t *ttdp, equiv_data_t *ed)
{
	return (equiv_node(stdp->t_tdesc, ttdp->t_tdesc, ed));
}