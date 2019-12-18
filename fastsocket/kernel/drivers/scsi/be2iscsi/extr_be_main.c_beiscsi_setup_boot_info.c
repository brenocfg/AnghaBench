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
struct iscsi_boot_kobj {int dummy; } ;
struct beiscsi_hba {int /*<<< orphan*/  boot_kset; TYPE_1__* shost; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  beiscsi_boot_release ; 
 int /*<<< orphan*/  beiscsi_eth_get_attr_visibility ; 
 scalar_t__ beiscsi_get_boot_info (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_ini_get_attr_visibility ; 
 int /*<<< orphan*/  beiscsi_show_boot_eth_info ; 
 int /*<<< orphan*/  beiscsi_show_boot_ini_info ; 
 int /*<<< orphan*/  beiscsi_show_boot_tgt_info ; 
 int /*<<< orphan*/  beiscsi_tgt_get_attr_visibility ; 
 struct iscsi_boot_kobj* iscsi_boot_create_ethernet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_boot_create_host_kset (int /*<<< orphan*/ ) ; 
 struct iscsi_boot_kobj* iscsi_boot_create_initiator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_boot_kobj* iscsi_boot_create_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_boot_destroy_kset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_get (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 

__attribute__((used)) static int beiscsi_setup_boot_info(struct beiscsi_hba *phba)
{
	struct iscsi_boot_kobj *boot_kobj;

	/* get boot info using mgmt cmd */
	if (beiscsi_get_boot_info(phba))
		/* Try to see if we can carry on without this */
		return 0;

	phba->boot_kset = iscsi_boot_create_host_kset(phba->shost->host_no);
	if (!phba->boot_kset)
		return -ENOMEM;

	/* get a ref because the show function will ref the phba */
	if (!scsi_host_get(phba->shost))
		goto free_kset;
	boot_kobj = iscsi_boot_create_target(phba->boot_kset, 0, phba,
					     beiscsi_show_boot_tgt_info,
					     beiscsi_tgt_get_attr_visibility,
					     beiscsi_boot_release);
	if (!boot_kobj)
		goto put_shost;

	if (!scsi_host_get(phba->shost))
		goto free_kset;
	boot_kobj = iscsi_boot_create_initiator(phba->boot_kset, 0, phba,
						beiscsi_show_boot_ini_info,
						beiscsi_ini_get_attr_visibility,
						beiscsi_boot_release);
	if (!boot_kobj)
		goto put_shost;

	if (!scsi_host_get(phba->shost))
		goto free_kset;
	boot_kobj = iscsi_boot_create_ethernet(phba->boot_kset, 0, phba,
					       beiscsi_show_boot_eth_info,
					       beiscsi_eth_get_attr_visibility,
					       beiscsi_boot_release);
	if (!boot_kobj)
		goto put_shost;
	return 0;

put_shost:
	scsi_host_put(phba->shost);
free_kset:
	iscsi_boot_destroy_kset(phba->boot_kset);
	return -ENOMEM;
}