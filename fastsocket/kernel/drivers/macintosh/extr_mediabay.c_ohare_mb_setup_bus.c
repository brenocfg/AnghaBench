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
typedef  int u8 ;
struct media_bay_info {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MB_BIC (struct media_bay_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_BIS (struct media_bay_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MB_CD 131 
#define  MB_FD 130 
#define  MB_FD1 129 
#define  MB_PCI 128 
 int /*<<< orphan*/  OHARE_FCR ; 
 int /*<<< orphan*/  OH_BAY_FLOPPY_ENABLE ; 
 int /*<<< orphan*/  OH_BAY_IDE_ENABLE ; 
 int /*<<< orphan*/  OH_BAY_PCI_ENABLE ; 
 int /*<<< orphan*/  OH_FLOPPY_ENABLE ; 
 int /*<<< orphan*/  OH_IDE1_RESET_N ; 

__attribute__((used)) static int
ohare_mb_setup_bus(struct media_bay_info* bay, u8 device_id)
{
	switch(device_id) {
		case MB_FD:
		case MB_FD1:
			MB_BIS(bay, OHARE_FCR, OH_BAY_FLOPPY_ENABLE);
			MB_BIS(bay, OHARE_FCR, OH_FLOPPY_ENABLE);
			return 0;
		case MB_CD:
			MB_BIC(bay, OHARE_FCR, OH_IDE1_RESET_N);
			MB_BIS(bay, OHARE_FCR, OH_BAY_IDE_ENABLE);
			return 0;
		case MB_PCI:
			MB_BIS(bay, OHARE_FCR, OH_BAY_PCI_ENABLE);
			return 0;
	}
	return -ENODEV;
}