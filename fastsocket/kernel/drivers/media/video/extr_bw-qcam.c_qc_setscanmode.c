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
struct qcam_device {int mode; int transfer_scale; int bpp; int port_mode; int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  QC_BIDIR 130 
 int QC_MODE_MASK ; 
#define  QC_NOTSET 129 
 int /*<<< orphan*/  QC_PARAM_CHANGE ; 
#define  QC_UNIDIR 128 

__attribute__((used)) static int qc_setscanmode(struct qcam_device *q)
{
	int old_mode = q->mode;

	switch (q->transfer_scale)
	{
		case 1:
			q->mode = 0;
			break;
		case 2:
			q->mode = 4;
			break;
		case 4:
			q->mode = 8;
			break;
	}

	switch (q->bpp)
	{
		case 4:
			break;
		case 6:
			q->mode += 2;
			break;
	}

	switch (q->port_mode & QC_MODE_MASK)
	{
		case QC_BIDIR:
			q->mode += 1;
			break;
		case QC_NOTSET:
		case QC_UNIDIR:
			break;
	}

	if (q->mode != old_mode)
		q->status |= QC_PARAM_CHANGE;

	return 0;
}