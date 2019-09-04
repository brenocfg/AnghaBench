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
struct kern_ctl_reg {char* ctl_name; int ctl_flags; int /*<<< orphan*/  ctl_rcvd; int /*<<< orphan*/  ctl_send; int /*<<< orphan*/  ctl_disconnect; int /*<<< orphan*/  ctl_connect; int /*<<< orphan*/  ctl_recvsize; int /*<<< orphan*/  ctl_sendsize; } ;
typedef  int /*<<< orphan*/  ctl_reg ;

/* Variables and functions */
 int CTL_FLAG_PRIVILEGED ; 
 int CTL_FLAG_REG_EXTENDED ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  FD_CTL_RCVBUFF_SIZE ; 
 int /*<<< orphan*/  FD_CTL_SENDBUFF_SIZE ; 
 int /*<<< orphan*/  FLOW_DIVERT_CONTROL_NAME ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int ctl_register (struct kern_ctl_reg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_divert_kctl_connect ; 
 int /*<<< orphan*/  flow_divert_kctl_disconnect ; 
 int /*<<< orphan*/  flow_divert_kctl_rcvd ; 
 int /*<<< orphan*/  flow_divert_kctl_send ; 
 int /*<<< orphan*/  g_flow_divert_kctl_ref ; 
 int /*<<< orphan*/  memset (struct kern_ctl_reg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nil_pcb ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
flow_divert_kctl_init(void)
{
	struct kern_ctl_reg	ctl_reg;
	int			result;

	memset(&ctl_reg, 0, sizeof(ctl_reg));

	strlcpy(ctl_reg.ctl_name, FLOW_DIVERT_CONTROL_NAME, sizeof(ctl_reg.ctl_name));
	ctl_reg.ctl_name[sizeof(ctl_reg.ctl_name)-1] = '\0';
	ctl_reg.ctl_flags = CTL_FLAG_PRIVILEGED | CTL_FLAG_REG_EXTENDED;
	ctl_reg.ctl_sendsize = FD_CTL_SENDBUFF_SIZE;
	ctl_reg.ctl_recvsize = FD_CTL_RCVBUFF_SIZE;

	ctl_reg.ctl_connect = flow_divert_kctl_connect;
	ctl_reg.ctl_disconnect = flow_divert_kctl_disconnect;
	ctl_reg.ctl_send = flow_divert_kctl_send;
	ctl_reg.ctl_rcvd = flow_divert_kctl_rcvd;

	result = ctl_register(&ctl_reg, &g_flow_divert_kctl_ref);

	if (result) {
		FDLOG(LOG_ERR, &nil_pcb, "flow_divert_kctl_init - ctl_register failed: %d\n", result);
		return result;
	}

	return 0;
}