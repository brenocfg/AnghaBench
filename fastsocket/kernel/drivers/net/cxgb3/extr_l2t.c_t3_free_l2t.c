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
struct l2t_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb_free_mem (struct l2t_data*) ; 

void t3_free_l2t(struct l2t_data *d)
{
	cxgb_free_mem(d);
}