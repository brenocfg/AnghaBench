#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ad_type; TYPE_2__* pcidev; TYPE_1__* enq; int /*<<< orphan*/  slot_num; } ;
typedef  TYPE_3__ ips_ha_t ;
struct TYPE_6__ {int device; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  revision; } ;
struct TYPE_5__ {int ucMaxPhysicalDevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_ADTYPE_KIOWA ; 
 int /*<<< orphan*/  IPS_ADTYPE_NAVAJO ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID2 ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID3 ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID3L ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID4H ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID4L ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID4LX ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID4M ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID4MX ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID5I1 ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID5I2 ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID6I ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID6M ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID7M ; 
 int /*<<< orphan*/  IPS_ADTYPE_SERVERAID7k ; 
#define  IPS_DEVICEID_COPPERHEAD 140 
#define  IPS_DEVICEID_MARCO 139 
#define  IPS_DEVICEID_MORPHEUS 138 
 int /*<<< orphan*/  IPS_REVID_CLARINETP1 ; 
 int /*<<< orphan*/  IPS_REVID_CLARINETP3 ; 
 int /*<<< orphan*/  IPS_REVID_NAVAJO ; 
 int /*<<< orphan*/  IPS_REVID_SERVERAID ; 
 int /*<<< orphan*/  IPS_REVID_SERVERAID2 ; 
 int /*<<< orphan*/  IPS_REVID_TROMBONE32 ; 
 int /*<<< orphan*/  IPS_REVID_TROMBONE64 ; 
#define  IPS_SUBDEVICEID_4L 137 
#define  IPS_SUBDEVICEID_4LX 136 
#define  IPS_SUBDEVICEID_4M 135 
#define  IPS_SUBDEVICEID_4MX 134 
#define  IPS_SUBDEVICEID_5I1 133 
#define  IPS_SUBDEVICEID_5I2 132 
#define  IPS_SUBDEVICEID_6I 131 
#define  IPS_SUBDEVICEID_6M 130 
#define  IPS_SUBDEVICEID_7M 129 
#define  IPS_SUBDEVICEID_7k 128 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 

__attribute__((used)) static void
ips_identify_controller(ips_ha_t * ha)
{
	METHOD_TRACE("ips_identify_controller", 1);

	switch (ha->pcidev->device) {
	case IPS_DEVICEID_COPPERHEAD:
		if (ha->pcidev->revision <= IPS_REVID_SERVERAID) {
			ha->ad_type = IPS_ADTYPE_SERVERAID;
		} else if (ha->pcidev->revision == IPS_REVID_SERVERAID2) {
			ha->ad_type = IPS_ADTYPE_SERVERAID2;
		} else if (ha->pcidev->revision == IPS_REVID_NAVAJO) {
			ha->ad_type = IPS_ADTYPE_NAVAJO;
		} else if ((ha->pcidev->revision == IPS_REVID_SERVERAID2)
			   && (ha->slot_num == 0)) {
			ha->ad_type = IPS_ADTYPE_KIOWA;
		} else if ((ha->pcidev->revision >= IPS_REVID_CLARINETP1) &&
			   (ha->pcidev->revision <= IPS_REVID_CLARINETP3)) {
			if (ha->enq->ucMaxPhysicalDevices == 15)
				ha->ad_type = IPS_ADTYPE_SERVERAID3L;
			else
				ha->ad_type = IPS_ADTYPE_SERVERAID3;
		} else if ((ha->pcidev->revision >= IPS_REVID_TROMBONE32) &&
			   (ha->pcidev->revision <= IPS_REVID_TROMBONE64)) {
			ha->ad_type = IPS_ADTYPE_SERVERAID4H;
		}
		break;

	case IPS_DEVICEID_MORPHEUS:
		switch (ha->pcidev->subsystem_device) {
		case IPS_SUBDEVICEID_4L:
			ha->ad_type = IPS_ADTYPE_SERVERAID4L;
			break;

		case IPS_SUBDEVICEID_4M:
			ha->ad_type = IPS_ADTYPE_SERVERAID4M;
			break;

		case IPS_SUBDEVICEID_4MX:
			ha->ad_type = IPS_ADTYPE_SERVERAID4MX;
			break;

		case IPS_SUBDEVICEID_4LX:
			ha->ad_type = IPS_ADTYPE_SERVERAID4LX;
			break;

		case IPS_SUBDEVICEID_5I2:
			ha->ad_type = IPS_ADTYPE_SERVERAID5I2;
			break;

		case IPS_SUBDEVICEID_5I1:
			ha->ad_type = IPS_ADTYPE_SERVERAID5I1;
			break;
		}

		break;

	case IPS_DEVICEID_MARCO:
		switch (ha->pcidev->subsystem_device) {
		case IPS_SUBDEVICEID_6M:
			ha->ad_type = IPS_ADTYPE_SERVERAID6M;
			break;
		case IPS_SUBDEVICEID_6I:
			ha->ad_type = IPS_ADTYPE_SERVERAID6I;
			break;
		case IPS_SUBDEVICEID_7k:
			ha->ad_type = IPS_ADTYPE_SERVERAID7k;
			break;
		case IPS_SUBDEVICEID_7M:
			ha->ad_type = IPS_ADTYPE_SERVERAID7M;
			break;
		}
		break;
	}
}