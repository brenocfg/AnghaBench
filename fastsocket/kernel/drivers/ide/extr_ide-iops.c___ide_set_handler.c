#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ expires; } ;
struct TYPE_5__ {TYPE_3__ timer; int /*<<< orphan*/  req_gen; int /*<<< orphan*/  req_gen_timer; int /*<<< orphan*/ * handler; } ;
typedef  TYPE_1__ ide_hwif_t ;
typedef  int /*<<< orphan*/  ide_handler_t ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 

void __ide_set_handler(ide_drive_t *drive, ide_handler_t *handler,
		       unsigned int timeout)
{
	ide_hwif_t *hwif = drive->hwif;

	BUG_ON(hwif->handler);
	hwif->handler		= handler;
	hwif->timer.expires	= jiffies + timeout;
	hwif->req_gen_timer	= hwif->req_gen;
	add_timer(&hwif->timer);
}