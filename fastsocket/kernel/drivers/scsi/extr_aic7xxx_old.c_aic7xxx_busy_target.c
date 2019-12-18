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
struct aic7xxx_scb {TYPE_1__* hscb; } ;
struct aic7xxx_host {int /*<<< orphan*/ * untagged_scbs; } ;
struct TYPE_2__ {size_t target_channel_lun; int /*<<< orphan*/  tag; } ;

/* Variables and functions */

__attribute__((used)) static inline void
aic7xxx_busy_target(struct aic7xxx_host *p, struct aic7xxx_scb *scb)
{
  p->untagged_scbs[scb->hscb->target_channel_lun] = scb->hscb->tag;
}