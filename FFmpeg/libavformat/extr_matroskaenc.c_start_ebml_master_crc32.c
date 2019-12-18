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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ write_crc; } ;
typedef  TYPE_1__ MatroskaMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  put_ebml_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ebml_void (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int start_ebml_master_crc32(AVIOContext *pb, AVIOContext **dyn_cp, MatroskaMuxContext *mkv,
                                   uint32_t elementid)
{
    int ret;

    if ((ret = avio_open_dyn_buf(dyn_cp)) < 0)
        return ret;

    put_ebml_id(pb, elementid);
    if (mkv->write_crc)
        put_ebml_void(*dyn_cp, 6); /* Reserve space for CRC32 so position/size calculations using avio_tell() take it into account */

    return 0;
}