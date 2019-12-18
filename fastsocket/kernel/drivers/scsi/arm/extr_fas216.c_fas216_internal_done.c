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
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_7__ {int internal_done; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;
typedef  TYPE_3__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  fas216_checkmagic (TYPE_3__*) ; 

__attribute__((used)) static void fas216_internal_done(struct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	fas216_checkmagic(info);

	info->internal_done = 1;
}