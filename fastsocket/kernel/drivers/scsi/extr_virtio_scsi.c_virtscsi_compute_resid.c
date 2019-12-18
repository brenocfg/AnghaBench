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
typedef  scalar_t__ u32 ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_4__ {scalar_t__ resid; int /*<<< orphan*/  length; } ;
struct TYPE_3__ {scalar_t__ resid; } ;

/* Variables and functions */
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_bidi_cmnd (struct scsi_cmnd*) ; 
 TYPE_2__* scsi_in (struct scsi_cmnd*) ; 
 TYPE_1__* scsi_out (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 

__attribute__((used)) static void virtscsi_compute_resid(struct scsi_cmnd *sc, u32 resid)
{
	if (!resid)
		return;

	if (!scsi_bidi_cmnd(sc)) {
		scsi_set_resid(sc, resid);
		return;
	}

	scsi_in(sc)->resid = min(resid, scsi_in(sc)->length);
	scsi_out(sc)->resid = resid - scsi_in(sc)->resid;
}