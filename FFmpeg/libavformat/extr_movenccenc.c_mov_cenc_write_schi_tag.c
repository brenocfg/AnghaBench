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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AES_CTR_IV_SIZE ; 
 int /*<<< orphan*/  CENC_KID_SIZE ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_cenc_write_schi_tag(AVIOContext *pb, uint8_t* kid)
{
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0);     /* size */
    ffio_wfourcc(pb, "schi");

    avio_wb32(pb, 32);    /* size */
    ffio_wfourcc(pb, "tenc");
    avio_wb32(pb, 0);     /* version & flags */
    avio_wb24(pb, 1);     /* is encrypted */
    avio_w8(pb, AES_CTR_IV_SIZE); /* iv size */
    avio_write(pb, kid, CENC_KID_SIZE);

    return update_size(pb, pos);
}