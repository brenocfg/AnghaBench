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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  auxiliary_info_entries; int /*<<< orphan*/  auxiliary_info_sizes; scalar_t__ use_subsamples; } ;
typedef  TYPE_1__ MOVMuxCencContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AES_CTR_IV_SIZE ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_cenc_write_saiz_tag(MOVMuxCencContext* ctx, AVIOContext *pb)
{
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "saiz");
    avio_wb32(pb, 0); /* version & flags */
    avio_w8(pb, ctx->use_subsamples ? 0 : AES_CTR_IV_SIZE);    /* default size*/
    avio_wb32(pb, ctx->auxiliary_info_entries); /* entry count */
    if (ctx->use_subsamples) {
        avio_write(pb, ctx->auxiliary_info_sizes, ctx->auxiliary_info_entries);
    }
    return update_size(pb, pos);
}