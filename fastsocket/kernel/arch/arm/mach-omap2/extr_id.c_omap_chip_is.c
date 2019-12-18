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
struct omap_chip_id {int oc; } ;
struct TYPE_2__ {int oc; } ;

/* Variables and functions */
 TYPE_1__ omap_chip ; 

int omap_chip_is(struct omap_chip_id oci)
{
	return (oci.oc & omap_chip.oc) ? 1 : 0;
}