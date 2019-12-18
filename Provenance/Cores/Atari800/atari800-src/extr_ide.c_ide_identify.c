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
struct ide_device {int cylinders; int heads; int sectors; char* drive_serial_str; int mult_sectors; int nb_sectors; scalar_t__ is_cdrom; scalar_t__ is_cf; int /*<<< orphan*/ * io_buffer; } ;

/* Variables and functions */
 int CAP_LBA_SUPPORTED ; 
 int GCBI_12BYTE_PACKETS ; 
 int GCBI_50US_TILL_DRQ ; 
 int GCBI_CDROM_DEVICE ; 
 int GCBI_FIXED_DRIVE ; 
 int GCBI_HAS_PACKET_FEAT_SET ; 
 int GCBI_HAS_REMOVABLE_MEDIA ; 
 int /*<<< orphan*/  LE16 (int /*<<< orphan*/ *,int,int) ; 
 int MAX_MULT_SECTORS ; 
 char* PACKAGE_VERSION ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  padstr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void ide_identify(struct ide_device *s) {
    unsigned int oldsize;
    uint8_t *p = s->io_buffer;
    memset(p, 0, 512);

    LE16(p, 0, GCBI_FIXED_DRIVE);
    LE16(p, 1, s->cylinders);
    LE16(p, 3, s->heads);
/*
    LE16(p, 4, 512 * s->sectors);   // bytes per track, obsolete ATA2
    LE16(p, 5, 512);                // bytes per sector, obsolete ATA2
*/
    LE16(p, 6, s->sectors);         /* sectors per track */

    padstr(p+10*2, s->drive_serial_str, 20);

/*
    LE16(p, 20, 3);                 // buffer type, obsolete ATA2
    LE16(p, 21, 16);                // cache size in sectors, obsolete ATA2
*/
    LE16(p, 22, 4);                 /* number of ECC bytes */

    padstr(p+23*2, PACKAGE_VERSION, 8);
    padstr(p+27*2, "ATARI800 HARDDISK", 40);

    if (MAX_MULT_SECTORS > 1)
        LE16(p, 47, 0x8000 | MAX_MULT_SECTORS);

    LE16(p, 48, 0);                 /* cannot perform double word I/O */
    LE16(p, 49, CAP_LBA_SUPPORTED);
    LE16(p, 51, 0x0200);            /* PIO transfer cycle */
/*
    LE16(p, 52, 0x0200);            // DMA transfer cycle, obsolete ATA3
*/
    LE16(p, 53, 1/*+2+4*/);         /* words 54-58[,64-70,88] are valid */
    LE16(p, 54, s->cylinders);
    LE16(p, 55, s->heads);
    LE16(p, 56, s->sectors);
    oldsize = s->cylinders * s->heads * s->sectors;
    LE16(p, 57, oldsize);
    LE16(p, 58, oldsize >> 16);
    if (s->mult_sectors)
        LE16(p, 59, 0x100 | s->mult_sectors);

    LE16(p, 60, s->nb_sectors);     /* total number of LBA sectors */
    LE16(p, 61, s->nb_sectors >> 16);

    if (s->is_cf) {
        LE16(p, 0, 0x848a);         /* CF Storage Card signature */
        padstr(p+27*2, "ATARI800 MICRODRIVE", 40);
        LE16(p, 49, CAP_LBA_SUPPORTED);
        LE16(p, 51, 2);
        LE16(p, 52, 1);
    }

    if (s->is_cdrom) {
        LE16(p, 0, GCBI_HAS_PACKET_FEAT_SET |
                   GCBI_CDROM_DEVICE        |
                   GCBI_HAS_REMOVABLE_MEDIA |
                   GCBI_50US_TILL_DRQ       |
                   GCBI_12BYTE_PACKETS);
        padstr(p+27*2, "ATARI800 DVD-ROM", 40);
        LE16(p, 49, CAP_LBA_SUPPORTED);
    }
}