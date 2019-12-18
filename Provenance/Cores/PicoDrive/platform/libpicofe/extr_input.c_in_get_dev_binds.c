#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int const* binds; } ;
typedef  TYPE_1__ in_dev_t ;

/* Variables and functions */
 TYPE_1__* get_dev (int) ; 

const int *in_get_dev_binds(int dev_id)
{
	in_dev_t *dev = get_dev(dev_id);

	return dev ? dev->binds : NULL;
}