#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * oformat; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {long long body_partitions_count; int /*<<< orphan*/  footer_partition_offset; int /*<<< orphan*/ * body_partition_offset; scalar_t__ edit_unit_byte_count; } ;
typedef  TYPE_1__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_mxf_opatom_muxer ; 
 int /*<<< orphan*/  klv_encode_ber_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  random_index_pack_key ; 

__attribute__((used)) static void mxf_write_random_index_pack(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    uint64_t pos = avio_tell(pb);
    int i;

    avio_write(pb, random_index_pack_key, 16);
    klv_encode_ber_length(pb, 28 + 12LL*mxf->body_partitions_count);

    if (mxf->edit_unit_byte_count && s->oformat != &ff_mxf_opatom_muxer)
        avio_wb32(pb, 1); // BodySID of header partition
    else
        avio_wb32(pb, 0);
    avio_wb64(pb, 0); // offset of header partition

    for (i = 0; i < mxf->body_partitions_count; i++) {
        avio_wb32(pb, 1); // BodySID
        avio_wb64(pb, mxf->body_partition_offset[i]);
    }

    avio_wb32(pb, 0); // BodySID of footer partition
    avio_wb64(pb, mxf->footer_partition_offset);

    avio_wb32(pb, avio_tell(pb) - pos + 4);
}