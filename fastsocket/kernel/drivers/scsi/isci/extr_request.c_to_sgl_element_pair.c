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
struct scu_sgl_element_pair {int dummy; } ;
struct isci_request {struct scu_sgl_element_pair* sg_table; TYPE_1__* tc; } ;
struct TYPE_2__ {struct scu_sgl_element_pair sgl_pair_cd; struct scu_sgl_element_pair sgl_pair_ab; } ;

/* Variables and functions */

__attribute__((used)) static struct scu_sgl_element_pair *to_sgl_element_pair(struct isci_request *ireq,
							int idx)
{
	if (idx == 0)
		return &ireq->tc->sgl_pair_ab;
	else if (idx == 1)
		return &ireq->tc->sgl_pair_cd;
	else if (idx < 0)
		return NULL;
	else
		return &ireq->sg_table[idx - 2];
}