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
struct hda_bus {struct azx* private_data; } ;
struct TYPE_2__ {unsigned int* res; } ;
struct azx {TYPE_1__ rirb; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int azx_single_get_response(struct hda_bus *bus,
					    unsigned int addr)
{
	struct azx *chip = bus->private_data;
	return chip->rirb.res[addr];
}