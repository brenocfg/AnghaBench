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
struct fc_internal {TYPE_1__* f; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_host_active_fc4s ) (struct Scsi_Host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fc_host_active_fc4s (struct Scsi_Host*) ; 
 int /*<<< orphan*/  show_fc_fc4s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct Scsi_Host*) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* transport_class_to_shost (struct device*) ; 

__attribute__((used)) static ssize_t
show_fc_host_active_fc4s (struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = transport_class_to_shost(dev);
	struct fc_internal *i = to_fc_internal(shost->transportt);

	if (i->f->get_host_active_fc4s)
		i->f->get_host_active_fc4s(shost);

	return (ssize_t)show_fc_fc4s(buf, fc_host_active_fc4s(shost));
}