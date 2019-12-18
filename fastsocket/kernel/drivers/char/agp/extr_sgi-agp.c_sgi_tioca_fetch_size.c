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
struct tioca_kernel {int ca_gfxap_size; int /*<<< orphan*/  ca_gfxgart_entries; } ;
struct TYPE_4__ {scalar_t__ dev_private_data; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  num_entries; } ;

/* Variables and functions */
 int MB (int) ; 
 TYPE_2__* agp_bridge ; 
 TYPE_1__* sgi_tioca_sizes ; 

__attribute__((used)) static int sgi_tioca_fetch_size(void)
{
	struct tioca_kernel *info =
	    (struct tioca_kernel *)agp_bridge->dev_private_data;

	sgi_tioca_sizes[0].size = info->ca_gfxap_size / MB(1);
	sgi_tioca_sizes[0].num_entries = info->ca_gfxgart_entries;

	return sgi_tioca_sizes[0].size;
}