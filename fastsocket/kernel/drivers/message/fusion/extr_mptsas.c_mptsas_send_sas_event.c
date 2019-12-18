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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mptsas_hotplug_event {int device_info; int /*<<< orphan*/  event_type; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; int /*<<< orphan*/  handle; } ;
struct fw_event_work {scalar_t__ event_data; int /*<<< orphan*/ * ioc; } ;
struct TYPE_2__ {int ReasonCode; int /*<<< orphan*/  SASAddress; int /*<<< orphan*/  PhyNum; int /*<<< orphan*/  TargetID; int /*<<< orphan*/  Bus; int /*<<< orphan*/  DevHandle; int /*<<< orphan*/  DeviceInfo; } ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;
typedef  TYPE_1__ EVENT_DATA_SAS_DEVICE_STATUS_CHANGE ;

/* Variables and functions */
#define  MPI_EVENT_SAS_DEV_STAT_RC_ADDED 132 
#define  MPI_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET 131 
#define  MPI_EVENT_SAS_DEV_STAT_RC_NOT_RESPONDING 130 
#define  MPI_EVENT_SAS_DEV_STAT_RC_NO_PERSIST_ADDED 129 
#define  MPI_EVENT_SAS_DEV_STAT_RC_SMART_DATA 128 
 int MPI_SAS_DEVICE_INFO_SATA_DEVICE ; 
 int MPI_SAS_DEVICE_INFO_SSP_TARGET ; 
 int MPI_SAS_DEVICE_INFO_STP_TARGET ; 
 int /*<<< orphan*/  MPI_SAS_OP_CLEAR_NOT_PRESENT ; 
 int /*<<< orphan*/  MPTSAS_ADD_DEVICE ; 
 int /*<<< orphan*/  MPTSAS_DEL_DEVICE ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct mptsas_hotplug_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mptbase_sas_persist_operation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptsas_free_fw_event (int /*<<< orphan*/ *,struct fw_event_work*) ; 
 int /*<<< orphan*/  mptsas_hotplug_work (int /*<<< orphan*/ *,struct fw_event_work*,struct mptsas_hotplug_event*) ; 

__attribute__((used)) static void
mptsas_send_sas_event(struct fw_event_work *fw_event)
{
	MPT_ADAPTER *ioc;
	struct mptsas_hotplug_event hot_plug_info;
	EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *sas_event_data;
	u32 device_info;
	u64 sas_address;

	ioc = fw_event->ioc;
	sas_event_data = (EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *)
	    fw_event->event_data;
	device_info = le32_to_cpu(sas_event_data->DeviceInfo);

	if ((device_info &
		(MPI_SAS_DEVICE_INFO_SSP_TARGET |
		MPI_SAS_DEVICE_INFO_STP_TARGET |
		MPI_SAS_DEVICE_INFO_SATA_DEVICE)) == 0) {
		mptsas_free_fw_event(ioc, fw_event);
		return;
	}

	if (sas_event_data->ReasonCode ==
		MPI_EVENT_SAS_DEV_STAT_RC_NO_PERSIST_ADDED) {
		mptbase_sas_persist_operation(ioc,
		MPI_SAS_OP_CLEAR_NOT_PRESENT);
		mptsas_free_fw_event(ioc, fw_event);
		return;
	}

	switch (sas_event_data->ReasonCode) {
	case MPI_EVENT_SAS_DEV_STAT_RC_NOT_RESPONDING:
	case MPI_EVENT_SAS_DEV_STAT_RC_ADDED:
		memset(&hot_plug_info, 0, sizeof(struct mptsas_hotplug_event));
		hot_plug_info.handle = le16_to_cpu(sas_event_data->DevHandle);
		hot_plug_info.channel = sas_event_data->Bus;
		hot_plug_info.id = sas_event_data->TargetID;
		hot_plug_info.phy_id = sas_event_data->PhyNum;
		memcpy(&sas_address, &sas_event_data->SASAddress,
		    sizeof(u64));
		hot_plug_info.sas_address = le64_to_cpu(sas_address);
		hot_plug_info.device_info = device_info;
		if (sas_event_data->ReasonCode &
		    MPI_EVENT_SAS_DEV_STAT_RC_ADDED)
			hot_plug_info.event_type = MPTSAS_ADD_DEVICE;
		else
			hot_plug_info.event_type = MPTSAS_DEL_DEVICE;
		mptsas_hotplug_work(ioc, fw_event, &hot_plug_info);
		break;

	case MPI_EVENT_SAS_DEV_STAT_RC_NO_PERSIST_ADDED:
		mptbase_sas_persist_operation(ioc,
		    MPI_SAS_OP_CLEAR_NOT_PRESENT);
		mptsas_free_fw_event(ioc, fw_event);
		break;

	case MPI_EVENT_SAS_DEV_STAT_RC_SMART_DATA:
	/* TODO */
	case MPI_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET:
	/* TODO */
	default:
		mptsas_free_fw_event(ioc, fw_event);
		break;
	}
}