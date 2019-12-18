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
struct lpfc_vport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_devloss_tmo ; 
 int /*<<< orphan*/  lpfc_devloss_tmo_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_discovery_threads ; 
 int /*<<< orphan*/  lpfc_discovery_threads_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_da_id ; 
 int /*<<< orphan*/  lpfc_enable_da_id_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_class ; 
 int /*<<< orphan*/  lpfc_fcp_class_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fdmi_on ; 
 int /*<<< orphan*/  lpfc_fdmi_on_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_log_verbose ; 
 int /*<<< orphan*/  lpfc_log_verbose_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_lun_queue_depth ; 
 int /*<<< orphan*/  lpfc_lun_queue_depth_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_max_luns ; 
 int /*<<< orphan*/  lpfc_max_luns_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_max_scsicmpl_time ; 
 int /*<<< orphan*/  lpfc_max_scsicmpl_time_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nodev_tmo ; 
 int /*<<< orphan*/  lpfc_nodev_tmo_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_peer_port_login ; 
 int /*<<< orphan*/  lpfc_peer_port_login_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_restrict_login ; 
 int /*<<< orphan*/  lpfc_restrict_login_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_scan_down ; 
 int /*<<< orphan*/  lpfc_scan_down_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_use_adisc ; 
 int /*<<< orphan*/  lpfc_use_adisc_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 

void
lpfc_get_vport_cfgparam(struct lpfc_vport *vport)
{
	lpfc_log_verbose_init(vport, lpfc_log_verbose);
	lpfc_lun_queue_depth_init(vport, lpfc_lun_queue_depth);
	lpfc_devloss_tmo_init(vport, lpfc_devloss_tmo);
	lpfc_nodev_tmo_init(vport, lpfc_nodev_tmo);
	lpfc_peer_port_login_init(vport, lpfc_peer_port_login);
	lpfc_restrict_login_init(vport, lpfc_restrict_login);
	lpfc_fcp_class_init(vport, lpfc_fcp_class);
	lpfc_use_adisc_init(vport, lpfc_use_adisc);
	lpfc_max_scsicmpl_time_init(vport, lpfc_max_scsicmpl_time);
	lpfc_fdmi_on_init(vport, lpfc_fdmi_on);
	lpfc_discovery_threads_init(vport, lpfc_discovery_threads);
	lpfc_max_luns_init(vport, lpfc_max_luns);
	lpfc_scan_down_init(vport, lpfc_scan_down);
	lpfc_enable_da_id_init(vport, lpfc_enable_da_id);
	return;
}