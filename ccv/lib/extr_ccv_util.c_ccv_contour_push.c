#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; } ;
typedef  TYPE_2__ ccv_point_t ;
struct TYPE_7__ {int x; int y; int width; int height; } ;
struct TYPE_9__ {int size; int m10; int m01; int m11; int m20; int m02; scalar_t__ set; TYPE_1__ rect; } ;
typedef  TYPE_3__ ccv_contour_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_push (scalar_t__,TYPE_2__*) ; 

void ccv_contour_push(ccv_contour_t* contour, ccv_point_t point)
{
	if (contour->size == 0)
	{
		contour->rect.x = point.x;
		contour->rect.y = point.y;
		contour->rect.width = contour->rect.height = 1;
		contour->m10 = point.x;
		contour->m01 = point.y;
		contour->m11 = point.x * point.y;
		contour->m20 = point.x * point.x;
		contour->m02 = point.y * point.y;
		contour->size = 1;
	} else {
		if (point.x < contour->rect.x)
		{
			contour->rect.width += contour->rect.x - point.x;
			contour->rect.x = point.x;
		} else if (point.x > contour->rect.x + contour->rect.width - 1) {
			contour->rect.width = point.x - contour->rect.x + 1;
		}
		if (point.y < contour->rect.y)
		{
			contour->rect.height += contour->rect.y - point.y;
			contour->rect.y = point.y;
		} else if (point.y > contour->rect.y + contour->rect.height - 1) {
			contour->rect.height = point.y - contour->rect.y + 1;
		}
		contour->m10 += point.x;
		contour->m01 += point.y;
		contour->m11 += point.x * point.y;
		contour->m20 += point.x * point.x;
		contour->m02 += point.y * point.y;
		contour->size++;
	}
	if (contour->set)
		ccv_array_push(contour->set, &point);
}