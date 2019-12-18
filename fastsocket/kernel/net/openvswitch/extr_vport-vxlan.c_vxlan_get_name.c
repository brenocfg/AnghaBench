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
struct vxlan_port {char const* name; } ;
struct vport {int dummy; } ;

/* Variables and functions */
 struct vxlan_port* vxlan_vport (struct vport const*) ; 

__attribute__((used)) static const char *vxlan_get_name(const struct vport *vport)
{
	struct vxlan_port *vxlan_port = vxlan_vport(vport);
	return vxlan_port->name;
}