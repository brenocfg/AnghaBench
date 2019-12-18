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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int WTV_SECTOR_SIZE ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_pad (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void write_fat(AVIOContext *pb, int start_sector, int nb_sectors, int shift)
{
    int i;
    for (i = 0; i < nb_sectors; i++) {
        avio_wl32(pb, start_sector + (i << shift));
    }
    // pad left sector pointer size
    write_pad(pb, WTV_SECTOR_SIZE - ((nb_sectors << 2) % WTV_SECTOR_SIZE));
}