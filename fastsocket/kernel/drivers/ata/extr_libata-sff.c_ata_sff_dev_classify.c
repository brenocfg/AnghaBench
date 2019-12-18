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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tf ;
struct ata_taskfile {int feature; } ;
struct ata_port {TYPE_2__* ops; } ;
struct ata_device {int horkage; int /*<<< orphan*/  devno; TYPE_1__* link; } ;
struct TYPE_4__ {scalar_t__ (* sff_check_status ) (struct ata_port*) ;int /*<<< orphan*/  (* sff_tf_read ) (struct ata_port*,struct ata_taskfile*) ;int /*<<< orphan*/  (* sff_dev_select ) (struct ata_port*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct ata_port* ap; } ;

/* Variables and functions */
 unsigned int ATA_DEV_ATA ; 
 unsigned int ATA_DEV_NONE ; 
 unsigned int ATA_DEV_UNKNOWN ; 
 int ATA_HORKAGE_DIAGNOSTIC ; 
 unsigned int ata_dev_classify (struct ata_taskfile*) ; 
 int /*<<< orphan*/  memset (struct ata_taskfile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*,struct ata_taskfile*) ; 
 scalar_t__ stub3 (struct ata_port*) ; 

unsigned int ata_sff_dev_classify(struct ata_device *dev, int present,
				  u8 *r_err)
{
	struct ata_port *ap = dev->link->ap;
	struct ata_taskfile tf;
	unsigned int class;
	u8 err;

	ap->ops->sff_dev_select(ap, dev->devno);

	memset(&tf, 0, sizeof(tf));

	ap->ops->sff_tf_read(ap, &tf);
	err = tf.feature;
	if (r_err)
		*r_err = err;

	/* see if device passed diags: continue and warn later */
	if (err == 0)
		/* diagnostic fail : do nothing _YET_ */
		dev->horkage |= ATA_HORKAGE_DIAGNOSTIC;
	else if (err == 1)
		/* do nothing */ ;
	else if ((dev->devno == 0) && (err == 0x81))
		/* do nothing */ ;
	else
		return ATA_DEV_NONE;

	/* determine if device is ATA or ATAPI */
	class = ata_dev_classify(&tf);

	if (class == ATA_DEV_UNKNOWN) {
		/* If the device failed diagnostic, it's likely to
		 * have reported incorrect device signature too.
		 * Assume ATA device if the device seems present but
		 * device signature is invalid with diagnostic
		 * failure.
		 */
		if (present && (dev->horkage & ATA_HORKAGE_DIAGNOSTIC))
			class = ATA_DEV_ATA;
		else
			class = ATA_DEV_NONE;
	} else if ((class == ATA_DEV_ATA) &&
		   (ap->ops->sff_check_status(ap) == 0))
		class = ATA_DEV_NONE;

	return class;
}