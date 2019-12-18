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
typedef  scalar_t__ iitype_t ;
struct TYPE_2__ {scalar_t__ ii_type; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */

int
iidesc_count_type(void *data, void *private)
{
	iidesc_t *ii = data;
	iitype_t match = (iitype_t)private;

	return (ii->ii_type == match);
}