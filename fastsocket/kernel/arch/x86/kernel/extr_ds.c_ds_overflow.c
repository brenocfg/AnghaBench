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
struct ds_context {TYPE_1__* pebs_master; TYPE_2__* bts_master; } ;
typedef  enum ds_qualifier { ____Placeholder_ds_qualifier } ds_qualifier ;
struct TYPE_4__ {int /*<<< orphan*/  (* ovfl ) (TYPE_2__*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* ovfl ) (TYPE_1__*) ;} ;

/* Variables and functions */
#define  ds_bts 129 
#define  ds_pebs 128 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

__attribute__((used)) static void ds_overflow(struct ds_context *context, enum ds_qualifier qual)
{
	switch (qual) {
	case ds_bts:
		if (context->bts_master &&
		    context->bts_master->ovfl)
			context->bts_master->ovfl(context->bts_master);
		break;
	case ds_pebs:
		if (context->pebs_master &&
		    context->pebs_master->ovfl)
			context->pebs_master->ovfl(context->pebs_master);
		break;
	}
}