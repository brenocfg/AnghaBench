#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int x; int y; } ;
struct TYPE_4__ {TYPE_1__ rect; } ;
typedef  TYPE_2__ ccv_root_comp_t ;

/* Variables and functions */
 double ccv_min (int,int) ; 

__attribute__((used)) static int _ccv_is_equal(const void* _r1, const void* _r2, void* data)
{
	const ccv_root_comp_t* r1 = (const ccv_root_comp_t*)_r1;
	const ccv_root_comp_t* r2 = (const ccv_root_comp_t*)_r2;
	int distance = (int)(ccv_min(r1->rect.width, r1->rect.height) * 0.25 + 0.5);

	return r2->rect.x <= r1->rect.x + distance &&
		r2->rect.x >= r1->rect.x - distance &&
		r2->rect.y <= r1->rect.y + distance &&
		r2->rect.y >= r1->rect.y - distance &&
		r2->rect.width <= (int)(r1->rect.width * 1.5 + 0.5) &&
		(int)(r2->rect.width * 1.5 + 0.5) >= r1->rect.width &&
		r2->rect.height <= (int)(r1->rect.height * 1.5 + 0.5) &&
		(int)(r2->rect.height * 1.5 + 0.5) >= r1->rect.height;
}