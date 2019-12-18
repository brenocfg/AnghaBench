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
struct lpfc_vport {TYPE_1__* phba; } ;
struct TYPE_2__ {char* ModelName; } ;

/* Variables and functions */
 int FW_REV_STR_SIZE ; 
 int /*<<< orphan*/  lpfc_decode_firmware_rev (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 char* lpfc_release_version ; 
 int snprintf (char*,size_t,char*,char*,char*,char*) ; 

int
lpfc_vport_symbolic_node_name(struct lpfc_vport *vport, char *symbol,
	size_t size)
{
	char fwrev[FW_REV_STR_SIZE];
	int n;

	lpfc_decode_firmware_rev(vport->phba, fwrev, 0);

	n = snprintf(symbol, size, "Emulex %s FV%s DV%s",
		vport->phba->ModelName, fwrev, lpfc_release_version);
	return n;
}