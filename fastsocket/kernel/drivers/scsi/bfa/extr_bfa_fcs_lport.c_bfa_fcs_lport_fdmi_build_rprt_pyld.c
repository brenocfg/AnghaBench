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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct fdmi_rprt_s {int /*<<< orphan*/  port_attr_blk; void* port_name; void* hba_id; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; } ;
struct bfa_fcs_lport_fdmi_s {TYPE_1__* ms; } ;
struct TYPE_2__ {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */
 struct bfa_fcs_lport_s* bfa_fcs_get_base_port (int /*<<< orphan*/ ) ; 
 int bfa_fcs_lport_fdmi_build_portattr_block (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ *) ; 
 void* bfa_fcs_lport_get_pwwn (struct bfa_fcs_lport_s*) ; 

__attribute__((used)) static          u16
bfa_fcs_lport_fdmi_build_rprt_pyld(struct bfa_fcs_lport_fdmi_s *fdmi, u8 *pyld)
{
	struct bfa_fcs_lport_s *port = fdmi->ms->port;
	struct fdmi_rprt_s *rprt = (struct fdmi_rprt_s *) pyld;
	u16        len;

	rprt->hba_id = bfa_fcs_lport_get_pwwn(bfa_fcs_get_base_port(port->fcs));
	rprt->port_name = bfa_fcs_lport_get_pwwn(port);

	len = bfa_fcs_lport_fdmi_build_portattr_block(fdmi,
				(u8 *) &rprt->port_attr_blk);

	len += sizeof(rprt->hba_id) + sizeof(rprt->port_name);

	return len;
}