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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct ide_device {int status; int* data_ptr; int* data_end; int /*<<< orphan*/  (* end_transfer_func ) (struct ide_device*) ;} ;

/* Variables and functions */
 int DRQ_STAT ; 
 scalar_t__ IDE_debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct ide_device*) ; 

__attribute__((used)) static void ide_data_writew(struct ide_device *s, int addr, uint16_t val) {
    uint8_t *p;

    if (IDE_debug) fprintf(stderr, "data_writew: %d, %04x\n", addr, val);

    /* PIO data access only when DRQ bit is set */
    if (!(s->status & DRQ_STAT)) return;

    /* LE16 */
    p           = s->data_ptr;
    p[0]        = val & 0xff;
    p[1]        = val >> 8;
    p          += 2;
    s->data_ptr = p;

    if (p >= s->data_end) s->end_transfer_func(s);
}