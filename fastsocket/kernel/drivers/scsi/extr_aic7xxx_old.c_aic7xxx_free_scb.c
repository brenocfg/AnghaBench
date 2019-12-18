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
struct aic7xxx_scb {TYPE_1__* hscb; scalar_t__ tag_action; scalar_t__ sg_length; scalar_t__ sg_count; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  flags; } ;
struct aic7xxx_host {TYPE_2__* scb_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  free_scbs; } ;
struct TYPE_3__ {int /*<<< orphan*/  target_channel_lun; scalar_t__ target_status; scalar_t__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_FREE ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  scbq_insert_head (int /*<<< orphan*/ *,struct aic7xxx_scb*) ; 

__attribute__((used)) static void
aic7xxx_free_scb(struct aic7xxx_host *p, struct aic7xxx_scb *scb)
{

  scb->flags = SCB_FREE;
  scb->cmd = NULL;
  scb->sg_count = 0;
  scb->sg_length = 0;
  scb->tag_action = 0;
  scb->hscb->control = 0;
  scb->hscb->target_status = 0;
  scb->hscb->target_channel_lun = SCB_LIST_NULL;

  scbq_insert_head(&p->scb_data->free_scbs, scb);
}