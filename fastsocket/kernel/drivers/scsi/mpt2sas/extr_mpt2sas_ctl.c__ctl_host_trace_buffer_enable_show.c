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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct MPT2SAS_ADAPTER {int* diag_buffer_status; int /*<<< orphan*/ * diag_buffer; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t MPI2_DIAG_BUF_TYPE_TRACE ; 
 int MPT2_DIAG_BUFFER_IS_REGISTERED ; 
 int MPT2_DIAG_BUFFER_IS_RELEASED ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct MPT2SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
_ctl_host_trace_buffer_enable_show(struct device *cdev,
    struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct MPT2SAS_ADAPTER *ioc = shost_priv(shost);

	if ((!ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE]) ||
	   ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT2_DIAG_BUFFER_IS_REGISTERED) == 0))
		return snprintf(buf, PAGE_SIZE, "off\n");
	else if ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT2_DIAG_BUFFER_IS_RELEASED))
		return snprintf(buf, PAGE_SIZE, "release\n");
	else
		return snprintf(buf, PAGE_SIZE, "post\n");
}