#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum scsi_host_state { ____Placeholder_scsi_host_state } scsi_host_state ;
struct TYPE_3__ {int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 size_t EINVAL ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 scalar_t__ scsi_host_set_state (struct Scsi_Host*,int) ; 
 TYPE_1__* shost_states ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int const) ; 

__attribute__((used)) static ssize_t
store_shost_state(struct device *dev, struct device_attribute *attr,
		  const char *buf, size_t count)
{
	int i;
	struct Scsi_Host *shost = class_to_shost(dev);
	enum scsi_host_state state = 0;

	for (i = 0; i < ARRAY_SIZE(shost_states); i++) {
		const int len = strlen(shost_states[i].name);
		if (strncmp(shost_states[i].name, buf, len) == 0 &&
		   buf[len] == '\n') {
			state = shost_states[i].value;
			break;
		}
	}
	if (!state)
		return -EINVAL;

	if (scsi_host_set_state(shost, state))
		return -EINVAL;
	return count;
}