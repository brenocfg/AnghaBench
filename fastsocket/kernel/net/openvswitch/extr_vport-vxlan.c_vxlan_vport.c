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
struct vxlan_port {int dummy; } ;
struct vport {int dummy; } ;

/* Variables and functions */
 struct vxlan_port* vport_priv (struct vport const*) ; 

__attribute__((used)) static inline struct vxlan_port *vxlan_vport(const struct vport *vport)
{
	return vport_priv(vport);
}