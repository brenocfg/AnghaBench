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
struct scsi_cmnd {TYPE_2__* device; } ;
struct mts_desc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  MTS_DEBUG_GOT_HERE () ; 
 int /*<<< orphan*/  mts_urb_abort (struct mts_desc*) ; 

__attribute__((used)) static int mts_scsi_abort(struct scsi_cmnd *srb)
{
	struct mts_desc* desc = (struct mts_desc*)(srb->device->host->hostdata[0]);

	MTS_DEBUG_GOT_HERE();

	mts_urb_abort(desc);

	return FAILED;
}