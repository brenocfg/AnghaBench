#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  DescDate; int /*<<< orphan*/  BoardRev; int /*<<< orphan*/  CpuRev; int /*<<< orphan*/  RamSize; int /*<<< orphan*/  RomSize; int /*<<< orphan*/  NumPorts; } ;
struct TYPE_6__ {int /*<<< orphan*/  BuildNumber; int /*<<< orphan*/  MinorVersion; int /*<<< orphan*/  MajorVersion; } ;
struct edgeport_product_info {int IsRS232; int IsRS422; int IsRS485; scalar_t__ ProductId; int /*<<< orphan*/  iDownloadFile; int /*<<< orphan*/  ManufactureDescDate; int /*<<< orphan*/  BootBuildNumber; int /*<<< orphan*/  BootMinorVersion; int /*<<< orphan*/  BootMajorVersion; int /*<<< orphan*/  BoardRev; int /*<<< orphan*/  CpuRev; int /*<<< orphan*/  RamSize; int /*<<< orphan*/  RomSize; scalar_t__ ProdInfoVer; int /*<<< orphan*/  NumPorts; } ;
struct edgeport_serial {TYPE_5__* serial; TYPE_2__ manuf_descriptor; TYPE_1__ boot_descriptor; struct edgeport_product_info product_info; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_10__ {TYPE_4__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_9__ {TYPE_3__ descriptor; } ;

/* Variables and functions */
 int DEVICE_ID_FROM_USB_PRODUCT_ID (scalar_t__) ; 
 int /*<<< orphan*/  EDGE_DOWNLOAD_FILE_80251 ; 
 int /*<<< orphan*/  EDGE_DOWNLOAD_FILE_I930 ; 
 int ION_DEVICE_ID_80251_NETCHIP ; 
#define  ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU 141 
#define  ION_DEVICE_ID_EDGEPORT_2 140 
#define  ION_DEVICE_ID_EDGEPORT_21 139 
#define  ION_DEVICE_ID_EDGEPORT_2I 138 
#define  ION_DEVICE_ID_EDGEPORT_2_DIN 137 
#define  ION_DEVICE_ID_EDGEPORT_4 136 
#define  ION_DEVICE_ID_EDGEPORT_421 135 
#define  ION_DEVICE_ID_EDGEPORT_4I 134 
#define  ION_DEVICE_ID_EDGEPORT_4T 133 
#define  ION_DEVICE_ID_EDGEPORT_4_DIN 132 
#define  ION_DEVICE_ID_EDGEPORT_8 131 
#define  ION_DEVICE_ID_EDGEPORT_8I 130 
#define  ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU 129 
#define  ION_DEVICE_ID_EDGEPORT_COMPATIBLE 128 
 int /*<<< orphan*/  dump_product_info (struct edgeport_product_info*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct edgeport_product_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void get_product_info(struct edgeport_serial *edge_serial)
{
	struct edgeport_product_info *product_info = &edge_serial->product_info;

	memset(product_info, 0, sizeof(struct edgeport_product_info));

	product_info->ProductId = (__u16)(le16_to_cpu(edge_serial->serial->dev->descriptor.idProduct) & ~ION_DEVICE_ID_80251_NETCHIP);
	product_info->NumPorts = edge_serial->manuf_descriptor.NumPorts;
	product_info->ProdInfoVer = 0;

	product_info->RomSize = edge_serial->manuf_descriptor.RomSize;
	product_info->RamSize = edge_serial->manuf_descriptor.RamSize;
	product_info->CpuRev = edge_serial->manuf_descriptor.CpuRev;
	product_info->BoardRev = edge_serial->manuf_descriptor.BoardRev;

	product_info->BootMajorVersion =
				edge_serial->boot_descriptor.MajorVersion;
	product_info->BootMinorVersion =
				edge_serial->boot_descriptor.MinorVersion;
	product_info->BootBuildNumber =
				edge_serial->boot_descriptor.BuildNumber;

	memcpy(product_info->ManufactureDescDate,
			edge_serial->manuf_descriptor.DescDate,
			sizeof(edge_serial->manuf_descriptor.DescDate));

	/* check if this is 2nd generation hardware */
	if (le16_to_cpu(edge_serial->serial->dev->descriptor.idProduct)
					    & ION_DEVICE_ID_80251_NETCHIP)
		product_info->iDownloadFile = EDGE_DOWNLOAD_FILE_80251;
	else
		product_info->iDownloadFile = EDGE_DOWNLOAD_FILE_I930;
 
	/* Determine Product type and set appropriate flags */
	switch (DEVICE_ID_FROM_USB_PRODUCT_ID(product_info->ProductId)) {
	case ION_DEVICE_ID_EDGEPORT_COMPATIBLE:
	case ION_DEVICE_ID_EDGEPORT_4T:
	case ION_DEVICE_ID_EDGEPORT_4:
	case ION_DEVICE_ID_EDGEPORT_2:
	case ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU:
	case ION_DEVICE_ID_EDGEPORT_8:
	case ION_DEVICE_ID_EDGEPORT_421:
	case ION_DEVICE_ID_EDGEPORT_21:
	case ION_DEVICE_ID_EDGEPORT_2_DIN:
	case ION_DEVICE_ID_EDGEPORT_4_DIN:
	case ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU:
		product_info->IsRS232 = 1;
		break;

	case ION_DEVICE_ID_EDGEPORT_2I:	/* Edgeport/2 RS422/RS485 */
		product_info->IsRS422 = 1;
		product_info->IsRS485 = 1;
		break;

	case ION_DEVICE_ID_EDGEPORT_8I:	/* Edgeport/4 RS422 */
	case ION_DEVICE_ID_EDGEPORT_4I:	/* Edgeport/4 RS422 */
		product_info->IsRS422 = 1;
		break;
	}

	dump_product_info(product_info);
}