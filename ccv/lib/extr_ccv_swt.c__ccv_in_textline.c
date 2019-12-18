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
struct TYPE_2__ {scalar_t__ left; scalar_t__ right; int dy; int dx; } ;
typedef  TYPE_1__ ccv_letter_pair_t ;

/* Variables and functions */

__attribute__((used)) static int _ccv_in_textline(const void* a, const void* b, void* data)
{
	ccv_letter_pair_t* pair1 = (ccv_letter_pair_t*)a;
	ccv_letter_pair_t* pair2 = (ccv_letter_pair_t*)b;
	if (pair1->left == pair2->left || pair1->right == pair2->right)
	{
		int tn = pair1->dy * pair2->dx - pair1->dx * pair2->dy;
		int td = pair1->dx * pair2->dx + pair1->dy * pair2->dy;
		// share the same end, opposite direction
		if (tn * 7 < -td * 4 && tn * 7 > td * 4)
			return 1;
	} else if (pair1->left == pair2->right || pair1->right == pair2->left) {
		int tn = pair1->dy * pair2->dx - pair1->dx * pair2->dy;
		int td = pair1->dx * pair2->dx + pair1->dy * pair2->dy;
		// share the other end, same direction
		if (tn * 7 < td * 4 && tn * 7 > -td * 4)
			return 1;
	}
	return 0;
}