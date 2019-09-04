#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  enum MXFMetadataSetType { ____Placeholder_MXFMetadataSetType } MXFMetadataSetType ;
struct TYPE_14__ {TYPE_2__* pb; TYPE_1__* priv_data; } ;
struct TYPE_13__ {scalar_t__ buf_ptr; } ;
struct TYPE_12__ {int /*<<< orphan*/  track_instance_count; int /*<<< orphan*/ * timecode_track; } ;
typedef  int /*<<< orphan*/  MXFPackage ;
typedef  TYPE_1__ MXFContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_KEY (TYPE_3__*,char*,scalar_t__) ; 
 int Sequence ; 
 int SourceClip ; 
 int TimecodeComponent ; 
 int /*<<< orphan*/  klv_encode_ber_length (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxf_write_common_fields (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxf_write_local_tag (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxf_write_refs_count (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxf_write_sequence(AVFormatContext *s, AVStream *st, MXFPackage *package)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    enum MXFMetadataSetType component;

    mxf_write_metadata_key(pb, 0x010f00);
    PRINT_KEY(s, "sequence key", pb->buf_ptr - 16);
    klv_encode_ber_length(pb, 80);

    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, Sequence, mxf->track_instance_count);

    PRINT_KEY(s, "sequence uid", pb->buf_ptr - 16);
    mxf_write_common_fields(s, st);

    // write structural component
    mxf_write_local_tag(pb, 16 + 8, 0x1001);
    mxf_write_refs_count(pb, 1);
    if (st == mxf->timecode_track)
        component = TimecodeComponent;
    else
        component = SourceClip;

    mxf_write_uuid(pb, component, mxf->track_instance_count);
}