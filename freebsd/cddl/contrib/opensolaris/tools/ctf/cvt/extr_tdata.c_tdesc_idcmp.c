#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ t_id; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */

int
tdesc_idcmp(void *arg1, void *arg2)
{
	tdesc_t *tdp1 = arg1, *tdp2 = arg2;

	if (tdp1->t_id == tdp2->t_id)
		return (0);
	else
		return (tdp1->t_id > tdp2->t_id ? 1 : -1);
}