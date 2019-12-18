#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct work_queue_wrapper {int /*<<< orphan*/  work; struct _MPT_SCSI_HOST* hd; } ;
struct _MPT_SCSI_HOST {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct work_queue_wrapper* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptspi_dv_renegotiate_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mptspi_dv_renegotiate(struct _MPT_SCSI_HOST *hd)
{
	struct work_queue_wrapper *wqw = kmalloc(sizeof(*wqw), GFP_ATOMIC);

	if (!wqw)
		return;

	INIT_WORK(&wqw->work, mptspi_dv_renegotiate_work);
	wqw->hd = hd;

	schedule_work(&wqw->work);
}