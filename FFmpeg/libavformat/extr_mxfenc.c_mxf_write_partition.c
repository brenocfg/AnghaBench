#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint64_t ;
typedef  unsigned int int64_t ;
struct TYPE_9__ {int nb_streams; int /*<<< orphan*/ * pb; int /*<<< orphan*/ * oformat; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int edit_units_count; unsigned int* body_partition_offset; int body_partitions_count; unsigned int footer_partition_offset; unsigned int body_offset; int /*<<< orphan*/  essence_container_count; scalar_t__ edit_unit_byte_count; } ;
typedef  TYPE_1__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 long long DESCRIPTOR_COUNT (int /*<<< orphan*/ ) ; 
 int KAG_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_reallocp_array (unsigned int**,int,int) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* body_partition_key ; 
 int /*<<< orphan*/  ff_mxf_opatom_muxer ; 
 int /*<<< orphan*/  const* footer_partition_key ; 
 int /*<<< orphan*/  klv_encode_ber4_length (int /*<<< orphan*/ *,int) ; 
 unsigned int klv_fill_size (unsigned int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mxf_write_essence_container_refs (TYPE_2__*) ; 
 int /*<<< orphan*/  mxf_write_header_metadata_sets (TYPE_2__*) ; 
 int /*<<< orphan*/  mxf_write_klv_fill (TYPE_2__*) ; 
 int /*<<< orphan*/  mxf_write_primer_pack (TYPE_2__*) ; 
 int /*<<< orphan*/  const* op1a_ul ; 
 int /*<<< orphan*/  const* opatom_ul ; 

__attribute__((used)) static int mxf_write_partition(AVFormatContext *s, int bodysid,
                                int indexsid,
                                const uint8_t *key, int write_metadata)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t header_byte_count_offset;
    unsigned index_byte_count = 0;
    uint64_t partition_offset = avio_tell(pb);
    int err;

    if (!mxf->edit_unit_byte_count && mxf->edit_units_count)
        index_byte_count = 85 + 12+(s->nb_streams+1)*6 +
            12+mxf->edit_units_count*15;
    else if (mxf->edit_unit_byte_count && indexsid)
        index_byte_count = 80;

    if (index_byte_count) {
        index_byte_count += 16 + 4; // add encoded ber4 length
        index_byte_count += klv_fill_size(index_byte_count);
    }

    if (key && !memcmp(key, body_partition_key, 16)) {
        if ((err = av_reallocp_array(&mxf->body_partition_offset, mxf->body_partitions_count + 1,
                                     sizeof(*mxf->body_partition_offset))) < 0) {
            mxf->body_partitions_count = 0;
            return err;
        }
        mxf->body_partition_offset[mxf->body_partitions_count++] = partition_offset;
    }

    // write klv
    if (key)
        avio_write(pb, key, 16);
    else
        avio_write(pb, body_partition_key, 16);

    klv_encode_ber4_length(pb, 88 + 16LL * DESCRIPTOR_COUNT(mxf->essence_container_count));

    // write partition value
    avio_wb16(pb, 1); // majorVersion
    avio_wb16(pb, 3); // minorVersion
    avio_wb32(pb, KAG_SIZE); // KAGSize

    avio_wb64(pb, partition_offset); // ThisPartition

    if (key && !memcmp(key, body_partition_key, 16) && mxf->body_partitions_count > 1)
        avio_wb64(pb, mxf->body_partition_offset[mxf->body_partitions_count-2]); // PreviousPartition
    else if (key && !memcmp(key, footer_partition_key, 16) && mxf->body_partitions_count)
        avio_wb64(pb, mxf->body_partition_offset[mxf->body_partitions_count-1]); // PreviousPartition
    else
        avio_wb64(pb, 0);

    avio_wb64(pb, mxf->footer_partition_offset); // footerPartition

    // set offset
    header_byte_count_offset = avio_tell(pb);
    avio_wb64(pb, 0); // headerByteCount, update later

    // indexTable
    avio_wb64(pb, index_byte_count); // indexByteCount
    avio_wb32(pb, index_byte_count ? indexsid : 0); // indexSID

    // BodyOffset
    if (bodysid && mxf->edit_units_count && mxf->body_partitions_count && s->oformat != &ff_mxf_opatom_muxer)
        avio_wb64(pb, mxf->body_offset);
    else
        avio_wb64(pb, 0);

    avio_wb32(pb, bodysid); // bodySID

    // operational pattern
    if (s->oformat == &ff_mxf_opatom_muxer)
        avio_write(pb, opatom_ul, 16);
    else
        avio_write(pb, op1a_ul, 16);

    // essence container
    mxf_write_essence_container_refs(s);

    if (write_metadata) {
        // mark the start of the headermetadata and calculate metadata size
        int64_t pos, start;
        unsigned header_byte_count;

        mxf_write_klv_fill(s);
        start = avio_tell(s->pb);
        mxf_write_primer_pack(s);
        mxf_write_klv_fill(s);
        mxf_write_header_metadata_sets(s);
        pos = avio_tell(s->pb);
        header_byte_count = pos - start + klv_fill_size(pos);

        // update header_byte_count
        avio_seek(pb, header_byte_count_offset, SEEK_SET);
        avio_wb64(pb, header_byte_count);
        avio_seek(pb, pos, SEEK_SET);
    }

    if(key)
        avio_flush(pb);

    return 0;
}