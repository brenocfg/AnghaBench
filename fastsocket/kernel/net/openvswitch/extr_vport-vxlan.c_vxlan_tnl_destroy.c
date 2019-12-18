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
struct vxlan_port {int /*<<< orphan*/  vs; } ;
struct vport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ovs_vport_deferred_free (struct vport*) ; 
 int /*<<< orphan*/  vxlan_sock_release (int /*<<< orphan*/ ) ; 
 struct vxlan_port* vxlan_vport (struct vport*) ; 

__attribute__((used)) static void vxlan_tnl_destroy(struct vport *vport)
{
	struct vxlan_port *vxlan_port = vxlan_vport(vport);

	vxlan_sock_release(vxlan_port->vs);

	ovs_vport_deferred_free(vport);
}