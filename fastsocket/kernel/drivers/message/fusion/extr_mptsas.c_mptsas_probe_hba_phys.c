#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int phy_id; scalar_t__ handle; scalar_t__ sas_address; } ;
struct mptsas_portinfo {int num_phys; int phy_id; struct mptsas_portinfo* phy_info; TYPE_8__ attached; TYPE_8__ identify; scalar_t__ handle; int /*<<< orphan*/  port_id; int /*<<< orphan*/  negotiated_link_rate; int /*<<< orphan*/  list; } ;
struct TYPE_11__ {int hba_port_num_phy; int num_ports; int /*<<< orphan*/  sas_index; TYPE_1__* sh; scalar_t__ hba_port_sas_addr; int /*<<< orphan*/  sas_topology_mutex; int /*<<< orphan*/  sas_topology; struct mptsas_portinfo* hba_port_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  shost_gendev; } ;
typedef  TYPE_2__ MPT_ADAPTER ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MPI_SAS_DEVICE_PGAD_FORM_HANDLE ; 
 int MPI_SAS_DEVICE_PGAD_FORM_SHIFT ; 
 int MPI_SAS_PHY_PGAD_FORM_PHY_NUMBER ; 
 int MPI_SAS_PHY_PGAD_FORM_SHIFT ; 
 int /*<<< orphan*/  kfree (struct mptsas_portinfo*) ; 
 struct mptsas_portinfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mptsas_probe_one_phy (int /*<<< orphan*/ *,struct mptsas_portinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mptsas_sas_device_pg0 (TYPE_2__*,TYPE_8__*,int,scalar_t__) ; 
 int mptsas_sas_io_unit_pg0 (TYPE_2__*,struct mptsas_portinfo*) ; 
 int /*<<< orphan*/  mptsas_sas_io_unit_pg1 (TYPE_2__*) ; 
 int /*<<< orphan*/  mptsas_sas_phy_pg0 (TYPE_2__*,struct mptsas_portinfo*,int,int) ; 
 int /*<<< orphan*/  mptsas_setup_wide_ports (TYPE_2__*,struct mptsas_portinfo*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mptsas_probe_hba_phys(MPT_ADAPTER *ioc)
{
	struct mptsas_portinfo *port_info, *hba;
	int error = -ENOMEM, i;

	hba = kzalloc(sizeof(struct mptsas_portinfo), GFP_KERNEL);
	if (! hba)
		goto out;

	error = mptsas_sas_io_unit_pg0(ioc, hba);
	if (error)
		goto out_free_port_info;

	mptsas_sas_io_unit_pg1(ioc);
	mutex_lock(&ioc->sas_topology_mutex);
	port_info = ioc->hba_port_info;
	if (!port_info) {
		ioc->hba_port_info = port_info = hba;
		ioc->hba_port_num_phy = port_info->num_phys;
		list_add_tail(&port_info->list, &ioc->sas_topology);
	} else {
		for (i = 0; i < hba->num_phys; i++) {
			port_info->phy_info[i].negotiated_link_rate =
				hba->phy_info[i].negotiated_link_rate;
			port_info->phy_info[i].handle =
				hba->phy_info[i].handle;
			port_info->phy_info[i].port_id =
				hba->phy_info[i].port_id;
		}
		kfree(hba->phy_info);
		kfree(hba);
		hba = NULL;
	}
	mutex_unlock(&ioc->sas_topology_mutex);
#if defined(CPQ_CIM)
	ioc->num_ports = port_info->num_phys;
#endif
	for (i = 0; i < port_info->num_phys; i++) {
		mptsas_sas_phy_pg0(ioc, &port_info->phy_info[i],
			(MPI_SAS_PHY_PGAD_FORM_PHY_NUMBER <<
			 MPI_SAS_PHY_PGAD_FORM_SHIFT), i);
		port_info->phy_info[i].identify.handle =
		    port_info->phy_info[i].handle;
		mptsas_sas_device_pg0(ioc, &port_info->phy_info[i].identify,
			(MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
			 MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
			 port_info->phy_info[i].identify.handle);
		if (!ioc->hba_port_sas_addr)
			ioc->hba_port_sas_addr =
			    port_info->phy_info[i].identify.sas_address;
		port_info->phy_info[i].identify.phy_id =
		    port_info->phy_info[i].phy_id = i;
		if (port_info->phy_info[i].attached.handle)
			mptsas_sas_device_pg0(ioc,
				&port_info->phy_info[i].attached,
				(MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
				 MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
				port_info->phy_info[i].attached.handle);
	}

	mptsas_setup_wide_ports(ioc, port_info);

	for (i = 0; i < port_info->num_phys; i++, ioc->sas_index++)
		mptsas_probe_one_phy(&ioc->sh->shost_gendev,
		    &port_info->phy_info[i], ioc->sas_index, 1);

	return 0;

 out_free_port_info:
	kfree(hba);
 out:
	return error;
}