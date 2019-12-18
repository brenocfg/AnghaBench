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
struct utun_pcb {int dummy; } ;
struct kern_ctl_reg {int ctl_flags; int ctl_sendsize; int ctl_recvsize; int /*<<< orphan*/  ctl_rcvd; int /*<<< orphan*/  ctl_getopt; int /*<<< orphan*/  ctl_setopt; int /*<<< orphan*/  ctl_send; int /*<<< orphan*/  ctl_disconnect; int /*<<< orphan*/  ctl_connect; int /*<<< orphan*/  ctl_bind; scalar_t__* ctl_name; } ;
typedef  int /*<<< orphan*/  kern_ctl ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int CTL_FLAG_PRIVILEGED ; 
 int CTL_FLAG_REG_EXTENDED ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTUN_CONTROL_NAME ; 
 int UTUN_PCB_ZONE_MAX ; 
 int /*<<< orphan*/  UTUN_PCB_ZONE_NAME ; 
 int /*<<< orphan*/  bzero (struct kern_ctl_reg*,int) ; 
 int /*<<< orphan*/  ctl_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ ctl_register (struct kern_ctl_reg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_tag_id_find (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ proto_register_plumber (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_unregister_plumber (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  utun_attach_proto ; 
 int /*<<< orphan*/  utun_ctl_bind ; 
 int /*<<< orphan*/  utun_ctl_connect ; 
 int /*<<< orphan*/  utun_ctl_disconnect ; 
 int /*<<< orphan*/  utun_ctl_getopt ; 
 int /*<<< orphan*/  utun_ctl_rcvd ; 
 int /*<<< orphan*/  utun_ctl_send ; 
 int /*<<< orphan*/  utun_ctl_setopt ; 
 int utun_family ; 
 int /*<<< orphan*/  utun_head ; 
 int /*<<< orphan*/  utun_kctlref ; 
 int /*<<< orphan*/  utun_lck_attr ; 
 int /*<<< orphan*/  utun_lck_grp ; 
 int /*<<< orphan*/  utun_lck_grp_attr ; 
 int /*<<< orphan*/  utun_lock ; 
 int utun_pcb_size ; 
 int /*<<< orphan*/ * utun_pcb_zone ; 
 int /*<<< orphan*/  utun_register_nexus () ; 
 int /*<<< orphan*/ * zinit (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
utun_register_control(void)
{
	struct kern_ctl_reg kern_ctl;
	errno_t result = 0;
	
	/* Find a unique value for our interface family */
	result = mbuf_tag_id_find(UTUN_CONTROL_NAME, &utun_family);
	if (result != 0) {
		printf("utun_register_control - mbuf_tag_id_find_internal failed: %d\n", result);
		return result;
	}

	utun_pcb_size = sizeof(struct utun_pcb);
	utun_pcb_zone = zinit(utun_pcb_size,
						  UTUN_PCB_ZONE_MAX * utun_pcb_size,
						  0, UTUN_PCB_ZONE_NAME);
	if (utun_pcb_zone == NULL) {
		printf("utun_register_control - zinit(utun_pcb) failed");
		return ENOMEM;
	}

#if UTUN_NEXUS
	utun_register_nexus();
#endif // UTUN_NEXUS

	TAILQ_INIT(&utun_head);
	
	bzero(&kern_ctl, sizeof(kern_ctl));
	strlcpy(kern_ctl.ctl_name, UTUN_CONTROL_NAME, sizeof(kern_ctl.ctl_name));
	kern_ctl.ctl_name[sizeof(kern_ctl.ctl_name) - 1] = 0;
	kern_ctl.ctl_flags = CTL_FLAG_PRIVILEGED | CTL_FLAG_REG_EXTENDED; /* Require root */
	kern_ctl.ctl_sendsize = 512 * 1024;
	kern_ctl.ctl_recvsize = 512 * 1024;
	kern_ctl.ctl_bind = utun_ctl_bind;
	kern_ctl.ctl_connect = utun_ctl_connect;
	kern_ctl.ctl_disconnect = utun_ctl_disconnect;
	kern_ctl.ctl_send = utun_ctl_send;
	kern_ctl.ctl_setopt = utun_ctl_setopt;
	kern_ctl.ctl_getopt = utun_ctl_getopt;
	kern_ctl.ctl_rcvd = utun_ctl_rcvd;

	result = ctl_register(&kern_ctl, &utun_kctlref);
	if (result != 0) {
		printf("utun_register_control - ctl_register failed: %d\n", result);
		return result;
	}
	
	/* Register the protocol plumbers */
	if ((result = proto_register_plumber(PF_INET, utun_family,
										 utun_attach_proto, NULL)) != 0) {
		printf("utun_register_control - proto_register_plumber(PF_INET, %d) failed: %d\n",
			   utun_family, result);
		ctl_deregister(utun_kctlref);
		return result;
	}
	
	/* Register the protocol plumbers */
	if ((result = proto_register_plumber(PF_INET6, utun_family,
										 utun_attach_proto, NULL)) != 0) {
		proto_unregister_plumber(PF_INET, utun_family);
		ctl_deregister(utun_kctlref);
		printf("utun_register_control - proto_register_plumber(PF_INET6, %d) failed: %d\n",
			   utun_family, result);
		return result;
	}

	utun_lck_attr = lck_attr_alloc_init();
	utun_lck_grp_attr = lck_grp_attr_alloc_init();
	utun_lck_grp = lck_grp_alloc_init("utun",  utun_lck_grp_attr);

	lck_mtx_init(&utun_lock, utun_lck_grp, utun_lck_attr);

	return 0;
}