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
struct TYPE_2__ {int /*<<< orphan*/  devno; } ;
struct dasd_diag_init_io {unsigned int block_size; int /*<<< orphan*/  end_block; int /*<<< orphan*/  flaga; int /*<<< orphan*/  offset; int /*<<< orphan*/  dev_nr; } ;
struct dasd_diag_private {TYPE_1__ dev_id; struct dasd_diag_init_io iib; } ;
struct dasd_device {scalar_t__ private; } ;
typedef  int /*<<< orphan*/  blocknum_t ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_DIAG_FLAGA_DEFAULT ; 
 int /*<<< orphan*/  INIT_BIO ; 
 int dia250 (struct dasd_diag_init_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dasd_diag_init_io*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
mdsk_init_io(struct dasd_device *device, unsigned int blocksize,
	     blocknum_t offset, blocknum_t *end_block)
{
	struct dasd_diag_private *private;
	struct dasd_diag_init_io *iib;
	int rc;

	private = (struct dasd_diag_private *) device->private;
	iib = &private->iib;
	memset(iib, 0, sizeof (struct dasd_diag_init_io));

	iib->dev_nr = private->dev_id.devno;
	iib->block_size = blocksize;
	iib->offset = offset;
	iib->flaga = DASD_DIAG_FLAGA_DEFAULT;

	rc = dia250(iib, INIT_BIO);

	if ((rc & 3) == 0 && end_block)
		*end_block = iib->end_block;

	return rc;
}