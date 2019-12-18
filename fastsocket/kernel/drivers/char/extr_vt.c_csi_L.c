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
struct vc_data {unsigned int vc_rows; unsigned int vc_y; scalar_t__ vc_need_wrap; int /*<<< orphan*/  vc_bottom; } ;

/* Variables and functions */
 int /*<<< orphan*/  scrdown (struct vc_data*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void csi_L(struct vc_data *vc, unsigned int nr)
{
	if (nr > vc->vc_rows - vc->vc_y)
		nr = vc->vc_rows - vc->vc_y;
	else if (!nr)
		nr = 1;
	scrdown(vc, vc->vc_y, vc->vc_bottom, nr);
	vc->vc_need_wrap = 0;
}