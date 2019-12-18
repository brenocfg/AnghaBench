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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  crc ;
struct TYPE_3__ {scalar_t__ write_crc; } ;
typedef  TYPE_1__ MatroskaMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CRC_32_IEEE_LE ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EBML_ID_CRC32 ; 
 int UINT32_MAX ; 
 int av_crc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_ebml_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_ebml_num (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_ebml_master_crc32(AVIOContext *pb, AVIOContext **dyn_cp, MatroskaMuxContext *mkv)
{
    uint8_t *buf, crc[4];
    int size, skip = 0;

    size = avio_close_dyn_buf(*dyn_cp, &buf);
    put_ebml_num(pb, size, 0);
    if (mkv->write_crc) {
        skip = 6; /* Skip reserved 6-byte long void element from the dynamic buffer. */
        AV_WL32(crc, av_crc(av_crc_get_table(AV_CRC_32_IEEE_LE), UINT32_MAX, buf + skip, size - skip) ^ UINT32_MAX);
        put_ebml_binary(pb, EBML_ID_CRC32, crc, sizeof(crc));
    }
    avio_write(pb, buf + skip, size - skip);

    av_free(buf);
    *dyn_cp = NULL;
}