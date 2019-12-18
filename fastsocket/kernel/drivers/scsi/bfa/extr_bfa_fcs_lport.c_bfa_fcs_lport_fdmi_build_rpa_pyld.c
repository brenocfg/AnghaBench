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
struct fdmi_rpa_s {int /*<<< orphan*/  port_attr_blk; int /*<<< orphan*/  port_name; } ;
struct bfa_fcs_lport_s {int dummy; } ;
struct bfa_fcs_lport_fdmi_s {TYPE_1__* ms; } ;
struct TYPE_2__ {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */
 int bfa_fcs_lport_fdmi_build_portattr_block (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_pwwn (struct bfa_fcs_lport_s*) ; 

__attribute__((used)) static          u16
bfa_fcs_lport_fdmi_build_rpa_pyld(struct bfa_fcs_lport_fdmi_s *fdmi, u8 *pyld)
{
	struct bfa_fcs_lport_s *port = fdmi->ms->port;
	struct fdmi_rpa_s *rpa = (struct fdmi_rpa_s *) pyld;
	u16        len;

	rpa->port_name = bfa_fcs_lport_get_pwwn(port);

	len = bfa_fcs_lport_fdmi_build_portattr_block(fdmi,
				(u8 *) &rpa->port_attr_blk);

	len += sizeof(rpa->port_name);

	return len;
}