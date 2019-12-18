#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ Id; } ;
struct TYPE_5__ {int /*<<< orphan*/  rc; int /*<<< orphan*/  data; int /*<<< orphan*/  status; scalar_t__ rc_count; TYPE_1__ e; int /*<<< orphan*/ * adapter; int /*<<< orphan*/ * os_ref; } ;
typedef  TYPE_2__ divas_um_idi_entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_UM_IDI_REMOVED ; 
 int /*<<< orphan*/  DIVA_UM_IDI_REMOVE_PENDING ; 
 int /*<<< orphan*/  diva_data_q_finit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_entity(divas_um_idi_entity_t * e)
{
	e->os_ref = NULL;
	e->status = 0;
	e->adapter = NULL;
	e->e.Id = 0;
	e->rc_count = 0;

	e->status |= DIVA_UM_IDI_REMOVED;
	e->status |= DIVA_UM_IDI_REMOVE_PENDING;

	diva_data_q_finit(&e->data);
	diva_data_q_finit(&e->rc);
}