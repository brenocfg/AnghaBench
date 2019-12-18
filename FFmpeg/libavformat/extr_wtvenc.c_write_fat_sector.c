#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int WTV_SECTOR_BITS ; 
 int WTV_SECTOR_SIZE ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int64_t write_fat_sector(AVFormatContext *s, int64_t start_pos, int nb_sectors, int sector_bits, int depth)
{
    int64_t start_sector = start_pos >> WTV_SECTOR_BITS;
    int shift = sector_bits - WTV_SECTOR_BITS;

    int64_t fat = avio_tell(s->pb);
    write_fat(s->pb, start_sector, nb_sectors, shift);

    if (depth == 2) {
        int64_t start_sector1 = fat >> WTV_SECTOR_BITS;
        int nb_sectors1 = ((nb_sectors << 2) + WTV_SECTOR_SIZE - 1) / WTV_SECTOR_SIZE;
        int64_t fat1 = avio_tell(s->pb);

       write_fat(s->pb, start_sector1, nb_sectors1, 0);
       return fat1;
    }

    return fat;
}