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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ide_device {int hob_feature; int error; int hob_nsector; int nsector; int hob_sector; int sector; int hob_lcyl; int lcyl; int hob_hcyl; int hcyl; int select; int status; } ;

/* Variables and functions */
 scalar_t__ IDE_debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static uint32_t ide_ioport_read(struct ide_device *s, uint16_t addr) {
    int ret = 0xff, hob = 0;

    addr &= 7;
    /* hob   = s->select & (1<<7); */
    /* FIXME: HOB stuff is broken/disabled in QEMU */

    switch(addr) {
    case 0: /* bottom ide layer does nothing here */        break;
    case 1: ret = hob ? s->hob_feature : s->error;          break;
    case 2: ret = hob ? s->hob_nsector : s->nsector & 0xff; break;
    case 3: ret = hob ? s->hob_sector  : s->sector;         break;
    case 4: ret = hob ? s->hob_lcyl    : s->lcyl;           break;
    case 5: ret = hob ? s->hob_hcyl    : s->hcyl;           break;
    case 6: ret = s->select;                                break;
    default:
    case 7: ret = s->status;                                break;
    }

    if (IDE_debug)
        fprintf(stderr, "ide: get: addr: %04x, ret: %02x\n", addr, ret);

    return ret;
}