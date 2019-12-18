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
struct nouveau_i2c_port {TYPE_1__* func; } ;
struct nouveau_disp {int dummy; } ;
struct dcb_output {int dummy; } ;
struct TYPE_2__ {int (* lnk_ctl ) (struct nouveau_i2c_port*,int,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct nouveau_i2c_port* nv50_pior_dp_find (struct nouveau_disp*,struct dcb_output*) ; 
 int stub1 (struct nouveau_i2c_port*,int,int,int) ; 

__attribute__((used)) static int
nv50_pior_dp_lnk_ctl(struct nouveau_disp *disp, struct dcb_output *outp,
		     int head, int lane_nr, int link_bw, bool enh)
{
	struct nouveau_i2c_port *port;
	int ret = -EINVAL;

	port = nv50_pior_dp_find(disp, outp);
	if (port && port->func->lnk_ctl)
		ret = port->func->lnk_ctl(port, lane_nr, link_bw, enh);

	return ret;
}