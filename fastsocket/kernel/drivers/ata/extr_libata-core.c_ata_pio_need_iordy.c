#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ata_device {scalar_t__ pio_mode; int /*<<< orphan*/  id; TYPE_2__* link; } ;
struct TYPE_4__ {TYPE_1__* ap; } ;
struct TYPE_3__ {int pflags; int flags; } ;

/* Variables and functions */
 int ATA_FLAG_NO_IORDY ; 
 int ATA_PFLAG_RESETTING ; 
 scalar_t__ XFER_PIO_2 ; 
 scalar_t__ XFER_PIO_5 ; 
 scalar_t__ XFER_PIO_6 ; 
 scalar_t__ ata_id_has_iordy (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_is_cfa (int /*<<< orphan*/ ) ; 

unsigned int ata_pio_need_iordy(const struct ata_device *adev)
{
	/* Don't set IORDY if we're preparing for reset.  IORDY may
	 * lead to controller lock up on certain controllers if the
	 * port is not occupied.  See bko#11703 for details.
	 */
	if (adev->link->ap->pflags & ATA_PFLAG_RESETTING)
		return 0;
	/* Controller doesn't support IORDY.  Probably a pointless
	 * check as the caller should know this.
	 */
	if (adev->link->ap->flags & ATA_FLAG_NO_IORDY)
		return 0;
	/* CF spec. r4.1 Table 22 says no iordy on PIO5 and PIO6.  */
	if (ata_id_is_cfa(adev->id)
	    && (adev->pio_mode == XFER_PIO_5 || adev->pio_mode == XFER_PIO_6))
		return 0;
	/* PIO3 and higher it is mandatory */
	if (adev->pio_mode > XFER_PIO_2)
		return 1;
	/* We turn it on when possible */
	if (ata_id_has_iordy(adev->id))
		return 1;
	return 0;
}