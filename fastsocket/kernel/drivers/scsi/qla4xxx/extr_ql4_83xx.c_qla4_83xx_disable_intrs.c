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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla4_83xx_disable_iocb_intrs (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_83xx_disable_mbox_intrs (struct scsi_qla_host*) ; 

void qla4_83xx_disable_intrs(struct scsi_qla_host *ha)
{
	qla4_83xx_disable_mbox_intrs(ha);
	qla4_83xx_disable_iocb_intrs(ha);
}