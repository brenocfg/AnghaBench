#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ alpha_agp_info ;
struct TYPE_7__ {TYPE_2__* dev_private_data; } ;
struct TYPE_5__ {int (* unbind ) (TYPE_2__*,int /*<<< orphan*/ ,struct agp_memory*) ;} ;

/* Variables and functions */
 TYPE_4__* agp_bridge ; 
 int /*<<< orphan*/  alpha_core_agp_tlbflush (struct agp_memory*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct agp_memory*) ; 

__attribute__((used)) static int alpha_core_agp_remove_memory(struct agp_memory *mem, off_t pg_start,
					int type)
{
	alpha_agp_info *agp = agp_bridge->dev_private_data;
	int status;

	status = agp->ops->unbind(agp, pg_start, mem);
	alpha_core_agp_tlbflush(mem);
	return status;
}