#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_10__ {int seekable; } ;
struct TYPE_9__ {scalar_t__ mode; scalar_t__ write_crc; } ;
typedef  TYPE_1__ MatroskaMuxContext ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 scalar_t__ MODE_WEBM ; 
 int avio_open_dyn_buf (TYPE_2__**) ; 
 int /*<<< orphan*/  put_ebml_void (TYPE_2__*,int) ; 
 int /*<<< orphan*/  start_ebml_master (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_ebml_master_crc32(AVIOContext *pb, AVIOContext **dyn_cp, MatroskaMuxContext *mkv,
                                   ebml_master *master, unsigned int elementid, uint64_t expectedsize)
{
    int ret;

    if ((ret = avio_open_dyn_buf(dyn_cp)) < 0)
        return ret;

    if (pb->seekable & AVIO_SEEKABLE_NORMAL) {
        *master = start_ebml_master(pb, elementid, expectedsize);
        if (mkv->write_crc && mkv->mode != MODE_WEBM)
            put_ebml_void(*dyn_cp, 6); /* Reserve space for CRC32 so position/size calculations using avio_tell() take it into account */
    } else
        *master = start_ebml_master(*dyn_cp, elementid, expectedsize);

    return 0;
}