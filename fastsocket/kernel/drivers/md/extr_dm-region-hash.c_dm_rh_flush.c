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
struct dm_region_hash {TYPE_2__* log; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int (* flush ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*) ; 

int dm_rh_flush(struct dm_region_hash *rh)
{
	return rh->log->type->flush(rh->log);
}