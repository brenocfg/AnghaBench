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
struct ide_device {void (* end_transfer_func ) (struct ide_device*) ;int /*<<< orphan*/  status; int /*<<< orphan*/  io_buffer; int /*<<< orphan*/  data_end; int /*<<< orphan*/  data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRQ_STAT ; 
 scalar_t__ IDE_debug ; 
 scalar_t__ count ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ide_transfer_stop(struct ide_device *s) {
    if (IDE_debug) fprintf(stderr, "transfer stop\n");

    s->end_transfer_func = ide_transfer_stop;
    s->data_ptr          = s->io_buffer;
    s->data_end          = s->io_buffer;
    s->status           &= ~DRQ_STAT;
    count                = 0;
}