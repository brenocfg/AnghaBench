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
typedef  int /*<<< orphan*/  u16 ;
struct cd_list_entry {unsigned int cd_flags; int /*<<< orphan*/ * id_firmware; scalar_t__ id_model; } ;

/* Variables and functions */
 size_t ATA_ID_FW_REV ; 
 size_t ATA_ID_PROD ; 
 struct cd_list_entry* ide_cd_quirks_list ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strstr (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ide_cd_flags(u16 *id)
{
	const struct cd_list_entry *cle = ide_cd_quirks_list;

	while (cle->id_model) {
		if (strcmp(cle->id_model, (char *)&id[ATA_ID_PROD]) == 0 &&
		    (cle->id_firmware == NULL ||
		     strstr((char *)&id[ATA_ID_FW_REV], cle->id_firmware)))
			return cle->cd_flags;
		cle++;
	}

	return 0;
}