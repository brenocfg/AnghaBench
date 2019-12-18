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
typedef  int /*<<< orphan*/  u32 ;
struct ata_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCR_CONTROL ; 
 int /*<<< orphan*/  __sata_set_spd_needed (struct ata_link*,int /*<<< orphan*/ *) ; 
 int sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sata_scr_write (struct ata_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sata_set_spd(struct ata_link *link)
{
	u32 scontrol;
	int rc;

	if ((rc = sata_scr_read(link, SCR_CONTROL, &scontrol)))
		return rc;

	if (!__sata_set_spd_needed(link, &scontrol))
		return 0;

	if ((rc = sata_scr_write(link, SCR_CONTROL, scontrol)))
		return rc;

	return 1;
}