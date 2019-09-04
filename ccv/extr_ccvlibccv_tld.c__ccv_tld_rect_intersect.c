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
struct TYPE_4__ {int width; int height; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ ccv_rect_t ;

/* Variables and functions */
 int ccv_max (scalar_t__,scalar_t__) ; 
 scalar_t__ ccv_min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline float _ccv_tld_rect_intersect(const ccv_rect_t r1, const ccv_rect_t r2)
{
	int intersect = ccv_max(0, ccv_min(r1.x + r1.width, r2.x + r2.width) - ccv_max(r1.x, r2.x)) * ccv_max(0, ccv_min(r1.y + r1.height, r2.y + r2.height) - ccv_max(r1.y, r2.y));
	return (float)intersect / (r1.width * r1.height + r2.width * r2.height - intersect);
}