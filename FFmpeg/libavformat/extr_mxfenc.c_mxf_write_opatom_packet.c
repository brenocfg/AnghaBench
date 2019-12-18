#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_15__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int header_written; size_t edit_units_count; int /*<<< orphan*/  body_offset; TYPE_1__* index_entries; int /*<<< orphan*/  edit_unit_byte_count; } ;
struct TYPE_13__ {int /*<<< orphan*/  temporal_ref; int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  temporal_ref; int /*<<< orphan*/  flags; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ MXFIndexEntry ;
typedef  TYPE_3__ MXFContext ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  header_open_partition_key ; 
 int /*<<< orphan*/  mxf_write_klv_fill (TYPE_5__*) ; 
 int mxf_write_opatom_body_partition (TYPE_5__*) ; 
 int mxf_write_partition (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mxf_write_opatom_packet(AVFormatContext *s, AVPacket *pkt, MXFIndexEntry *ie)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;

    int err;

    if (!mxf->header_written) {
        if ((err = mxf_write_partition(s, 0, 0, header_open_partition_key, 1)) < 0)
            return err;
        mxf_write_klv_fill(s);

        if ((err = mxf_write_opatom_body_partition(s)) < 0)
            return err;
        mxf->header_written = 1;
    }

    if (!mxf->edit_unit_byte_count) {
        mxf->index_entries[mxf->edit_units_count].offset = mxf->body_offset;
        mxf->index_entries[mxf->edit_units_count].flags = ie->flags;
        mxf->index_entries[mxf->edit_units_count].temporal_ref = ie->temporal_ref;
    }
    mxf->edit_units_count++;
    avio_write(pb, pkt->data, pkt->size);
    mxf->body_offset += pkt->size;
    avio_flush(pb);

    return 0;
}