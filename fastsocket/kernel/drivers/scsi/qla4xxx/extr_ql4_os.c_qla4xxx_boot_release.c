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
struct scsi_qla_host {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4xxx_boot_release(void *data)
{
	struct scsi_qla_host *ha = data;

	scsi_host_put(ha->host);
}