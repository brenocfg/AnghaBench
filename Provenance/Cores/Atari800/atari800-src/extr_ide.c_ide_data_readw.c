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
 int count ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct ide_device*) ; 

__attribute__((used)) static uint16_t ide_data_readw(struct ide_device *s, int addr) {
    uint8_t *p;
    uint16_t ret;

    /* PIO data access only when DRQ bit is set */
    if (!(s->status & DRQ_STAT)) return 0;

    /* LE16 */
    p           = s->data_ptr;
    ret         = p[0];
    ret        |= p[1] << 8;
    p          += 2;
    s->data_ptr = p;

    if (IDE_debug) {
        fprintf(stderr, "data_readw: %d, %04x (count: %d)\n", addr, ret, count);
        count++;
        count &= 0xff;
    }

    if (p >= s->data_end) s->end_transfer_func(s);

    return ret;
}