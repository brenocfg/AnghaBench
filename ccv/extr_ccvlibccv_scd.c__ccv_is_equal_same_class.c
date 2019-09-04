#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x; int width; int y; int height; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_6__ {TYPE_2__ rect; TYPE_1__ classification; } ;
typedef  TYPE_3__ ccv_comp_t ;

/* Variables and functions */
 int ccv_max (int,int) ; 
 int ccv_min (int,int) ; 

__attribute__((used)) static int _ccv_is_equal_same_class(const void* _r1, const void* _r2, void* data)
{
	const ccv_comp_t* r1 = (const ccv_comp_t*)_r1;
	const ccv_comp_t* r2 = (const ccv_comp_t*)_r2;

	if (r2->classification.id != r1->classification.id)
		return 0;

	int i = ccv_max(ccv_min(r2->rect.x + r2->rect.width, r1->rect.x + r1->rect.width) - ccv_max(r2->rect.x, r1->rect.x), 0) * ccv_max(ccv_min(r2->rect.y + r2->rect.height, r1->rect.y + r1->rect.height) - ccv_max(r2->rect.y, r1->rect.y), 0);
	int m = ccv_min(r2->rect.width * r2->rect.height, r1->rect.width * r1->rect.height);

	return i >= 0.3 * m; // IoM > 0.3 like HeadHunter does
}