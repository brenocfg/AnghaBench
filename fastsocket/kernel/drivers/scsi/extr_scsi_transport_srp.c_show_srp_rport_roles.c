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
struct srp_rport {scalar_t__ roles; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {scalar_t__ value; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_1__* srp_rport_role_names ; 
 struct srp_rport* transport_class_to_srp_rport (struct device*) ; 

__attribute__((used)) static ssize_t
show_srp_rport_roles(struct device *dev, struct device_attribute *attr,
		     char *buf)
{
	struct srp_rport *rport = transport_class_to_srp_rport(dev);
	int i;
	char *name = NULL;

	for (i = 0; i < ARRAY_SIZE(srp_rport_role_names); i++)
		if (srp_rport_role_names[i].value == rport->roles) {
			name = srp_rport_role_names[i].name;
			break;
		}
	return sprintf(buf, "%s\n", name ? : "unknown");
}