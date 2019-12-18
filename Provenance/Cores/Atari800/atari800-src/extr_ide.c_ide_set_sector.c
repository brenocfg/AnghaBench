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
struct ide_device {int select; int hcyl; int lcyl; int sector; int hob_sector; int hob_lcyl; int hob_hcyl; int heads; int sectors; int /*<<< orphan*/  lba48; } ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static void ide_set_sector(struct ide_device *s, int64_t sector_num) {
    unsigned int cyl, r;

    if (s->select & 0x40) {
        if (!s->lba48) {
            s->select = (s->select & 0xf0) | (sector_num >> 24);
            s->hcyl   =                       sector_num >> 16 ;
            s->lcyl   =                       sector_num >>  8 ;
            s->sector =                       sector_num       ;
        } else {
            s->sector     = sector_num      ;
            s->lcyl       = sector_num >>  8;
            s->hcyl       = sector_num >> 16;
            s->hob_sector = sector_num >> 24;
            s->hob_lcyl   = sector_num >> 32;
            s->hob_hcyl   = sector_num >> 40;
        }
    } else {
        cyl = sector_num / (s->heads * s->sectors);
        r   = sector_num % (s->heads * s->sectors);

        s->hcyl   = cyl >> 8;
        s->lcyl   = cyl     ;
        s->select = (s->select & 0xf0) | ((r / s->sectors) & 0x0f);
        s->sector =                       (r % s->sectors) + 1;
    }
}