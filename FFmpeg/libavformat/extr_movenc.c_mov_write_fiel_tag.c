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
typedef  int /*<<< orphan*/  MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (unsigned int*) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 unsigned int* fiel_data ; 

__attribute__((used)) static int mov_write_fiel_tag(AVIOContext *pb, MOVTrack *track, int field_order)
{
    unsigned mov_field_order = 0;
    if (field_order < FF_ARRAY_ELEMS(fiel_data))
        mov_field_order = fiel_data[field_order];
    else
        return 0;
    avio_wb32(pb, 10);
    ffio_wfourcc(pb, "fiel");
    avio_wb16(pb, mov_field_order);
    return 10;
}