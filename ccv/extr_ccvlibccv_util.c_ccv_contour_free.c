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
struct TYPE_4__ {scalar_t__ set; } ;
typedef  TYPE_1__ ccv_contour_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ccv_array_free (scalar_t__) ; 

void ccv_contour_free(ccv_contour_t* contour)
{
	if (contour->set)
		ccv_array_free(contour->set);
	ccfree(contour);
}