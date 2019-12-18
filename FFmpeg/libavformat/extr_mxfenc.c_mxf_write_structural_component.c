#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_5__* pb; TYPE_3__* priv_data; } ;
struct TYPE_24__ {scalar_t__ buf_ptr; } ;
struct TYPE_23__ {scalar_t__ index; } ;
struct TYPE_22__ {int /*<<< orphan*/  track_instance_count; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_1__* ref; } ;
struct TYPE_20__ {int /*<<< orphan*/  instance; } ;
typedef  TYPE_2__ MXFPackage ;
typedef  TYPE_3__ MXFContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_KEY (TYPE_6__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  SourceClip ; 
 scalar_t__ SourcePackage ; 
 int /*<<< orphan*/  avio_wb32 (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  avio_wb64 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  klv_encode_ber_length (TYPE_5__*,int) ; 
 int /*<<< orphan*/  mxf_write_common_fields (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mxf_write_local_tag (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (TYPE_5__*,int) ; 
 int /*<<< orphan*/  mxf_write_umid (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_uuid (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxf_write_structural_component(AVFormatContext *s, AVStream *st, MXFPackage *package)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int i;

    mxf_write_metadata_key(pb, 0x011100);
    PRINT_KEY(s, "sturctural component key", pb->buf_ptr - 16);
    klv_encode_ber_length(pb, 108);

    // write uid
    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, SourceClip, mxf->track_instance_count);

    PRINT_KEY(s, "structural component uid", pb->buf_ptr - 16);
    mxf_write_common_fields(s, st);

    // write start_position
    mxf_write_local_tag(pb, 8, 0x1201);
    avio_wb64(pb, 0);

    // write source package uid, end of the reference
    mxf_write_local_tag(pb, 32, 0x1101);
    if (!package->ref) {
        for (i = 0; i < 4; i++)
            avio_wb64(pb, 0);
    } else
        mxf_write_umid(s, package->ref->instance);

    // write source track id
    mxf_write_local_tag(pb, 4, 0x1102);
    if (package->type == SourcePackage && !package->ref)
        avio_wb32(pb, 0);
    else
        avio_wb32(pb, st->index+2);
}