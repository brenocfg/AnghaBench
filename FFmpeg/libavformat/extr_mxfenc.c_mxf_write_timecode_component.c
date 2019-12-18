#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  start; } ;
struct TYPE_7__ {TYPE_1__ tc; int /*<<< orphan*/  timecode_base; int /*<<< orphan*/  track_instance_count; } ;
typedef  int /*<<< orphan*/  MXFPackage ;
typedef  TYPE_2__ MXFContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AV_TIMECODE_FLAG_DROPFRAME ; 
 int /*<<< orphan*/  TimecodeComponent ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  klv_encode_ber_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxf_write_common_fields (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxf_write_local_tag (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxf_write_timecode_component(AVFormatContext *s, AVStream *st, MXFPackage *package)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;

    mxf_write_metadata_key(pb, 0x011400);
    klv_encode_ber_length(pb, 75);

    // UID
    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, TimecodeComponent, mxf->track_instance_count);

    mxf_write_common_fields(s, st);

    // Start Time Code
    mxf_write_local_tag(pb, 8, 0x1501);
    avio_wb64(pb, mxf->tc.start);

    // Rounded Time Code Base
    mxf_write_local_tag(pb, 2, 0x1502);
    avio_wb16(pb, mxf->timecode_base);

    // Drop Frame
    mxf_write_local_tag(pb, 1, 0x1503);
    avio_w8(pb, !!(mxf->tc.flags & AV_TIMECODE_FLAG_DROPFRAME));
}