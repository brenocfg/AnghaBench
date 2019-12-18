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
typedef  int /*<<< orphan*/  uint8_t ;
struct ide_device {int status; scalar_t__ cycle; int /*<<< orphan*/ * data_end; int /*<<< orphan*/ * data_ptr; int /*<<< orphan*/ * end_transfer_func; } ;
typedef  int /*<<< orphan*/  EndTransferFunc ;

/* Variables and functions */
 int DRQ_STAT ; 
 int ERR_STAT ; 
 scalar_t__ IDE_debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ide_transfer_start(struct ide_device *s, uint8_t *buf, int size,
                                       EndTransferFunc *end_transfer_func) {
    if (IDE_debug) fprintf(stderr, "transfer start\n");

    s->end_transfer_func = end_transfer_func;
    s->data_ptr          = buf;
    s->data_end          = buf + size;
    s->cycle             = 0;

    if (!(s->status & ERR_STAT)) s->status |= DRQ_STAT;
}