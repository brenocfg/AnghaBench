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
struct ide_device {int feature; int error; int nsector; int sector; int lcyl; int hcyl; int select; int status; scalar_t__ media_changed; int /*<<< orphan*/  (* end_transfer_func ) (struct ide_device*) ;scalar_t__ is_cdrom; scalar_t__ lba48; scalar_t__ hob_hcyl; scalar_t__ hob_lcyl; scalar_t__ hob_nsector; scalar_t__ hob_sector; scalar_t__ hob_feature; scalar_t__ mult_sectors; scalar_t__ is_cf; } ;

/* Variables and functions */
 scalar_t__ IDE_debug ; 
 scalar_t__ MAX_MULT_SECTORS ; 
 int READY_STAT ; 
 int SEEK_STAT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ide_dummy_transfer_stop (struct ide_device*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ide_reset(struct ide_device *s) {
    if (IDE_debug) fprintf(stderr, "ide: reset\n");

    if (s->is_cf) s->mult_sectors = 0;
    else          s->mult_sectors = MAX_MULT_SECTORS;

    /* ide regs */
    s->feature = s->error = s->nsector = s->sector = s->lcyl = s->hcyl = 0;

    /* lba48 */
    s->hob_feature = s->hob_sector = s->hob_nsector =
    s->hob_lcyl = s->hob_hcyl = s->lba48 = 0;

    s->select = 0xa0;
    s->status = READY_STAT | SEEK_STAT;

    /* ATAPI stuff skipped */

    s->select &= 0xf0;  /* clear head */
    s->nsector = s->sector = 1;
    if (s->is_cdrom) {
        s->lcyl = 0x14;
        s->hcyl = 0xeb;
    } else {
        s->lcyl = s->hcyl = 0;
    }

    s->end_transfer_func = ide_dummy_transfer_stop;
    ide_dummy_transfer_stop(s);
    s->media_changed = 0;
}