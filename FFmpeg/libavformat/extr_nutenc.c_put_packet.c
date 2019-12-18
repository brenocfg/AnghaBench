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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  NUTContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_crc04C11DB7_update ; 
 int /*<<< orphan*/  ff_put_v (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_get_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_init_checksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_packet(NUTContext *nut, AVIOContext *bc, AVIOContext *dyn_bc,
                       int calculate_checksum, uint64_t startcode)
{
    uint8_t *dyn_buf = NULL;
    int dyn_size     = avio_close_dyn_buf(dyn_bc, &dyn_buf);
    int forw_ptr     = dyn_size + 4 * calculate_checksum;

    if (forw_ptr > 4096)
        ffio_init_checksum(bc, ff_crc04C11DB7_update, 0);
    avio_wb64(bc, startcode);
    ff_put_v(bc, forw_ptr);
    if (forw_ptr > 4096)
        avio_wl32(bc, ffio_get_checksum(bc));

    if (calculate_checksum)
        ffio_init_checksum(bc, ff_crc04C11DB7_update, 0);
    avio_write(bc, dyn_buf, dyn_size);
    if (calculate_checksum)
        avio_wl32(bc, ffio_get_checksum(bc));

    av_free(dyn_buf);
}