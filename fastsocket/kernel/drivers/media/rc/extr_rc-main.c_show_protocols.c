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
typedef  int u64 ;
struct TYPE_5__ {int rc_type; } ;
struct rc_dev {scalar_t__ driver_type; int allowed_protos; TYPE_2__* raw; TYPE_1__ rc_map; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_7__ {int type; char* name; } ;
struct TYPE_6__ {int enabled_protocols; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IR_dprintk (int,char*,long long,long long) ; 
 scalar_t__ RC_DRIVER_SCANCODE ; 
 int ir_raw_get_allowed_protocols () ; 
 TYPE_3__* proto_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct rc_dev* to_rc_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_protocols(struct device *device,
			      struct device_attribute *mattr, char *buf)
{
	struct rc_dev *dev = to_rc_dev(device);
	u64 allowed, enabled;
	char *tmp = buf;
	int i;

	/* Device is being removed */
	if (!dev)
		return -EINVAL;

	if (dev->driver_type == RC_DRIVER_SCANCODE) {
		enabled = dev->rc_map.rc_type;
		allowed = dev->allowed_protos;
	} else {
		enabled = dev->raw->enabled_protocols;
		allowed = ir_raw_get_allowed_protocols();
	}

	IR_dprintk(1, "allowed - 0x%llx, enabled - 0x%llx\n",
		   (long long)allowed,
		   (long long)enabled);

	for (i = 0; i < ARRAY_SIZE(proto_names); i++) {
		if (allowed & enabled & proto_names[i].type)
			tmp += sprintf(tmp, "[%s] ", proto_names[i].name);
		else if (allowed & proto_names[i].type)
			tmp += sprintf(tmp, "%s ", proto_names[i].name);
	}

	if (tmp != buf)
		tmp--;
	*tmp = '\n';
	return tmp + 1 - buf;
}