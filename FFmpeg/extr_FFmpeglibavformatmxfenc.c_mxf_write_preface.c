#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/ * oformat; TYPE_2__* pb; TYPE_1__* priv_data; } ;
struct TYPE_17__ {scalar_t__ buf_ptr; } ;
struct TYPE_16__ {int /*<<< orphan*/  essence_container_count; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ MXFContext ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ContentStorage ; 
 long long DESCRIPTOR_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Identification ; 
 int /*<<< orphan*/  PRINT_KEY (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  Preface ; 
 int /*<<< orphan*/  avio_wb16 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  avio_wb32 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  avio_wb64 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_mxf_opatom_muxer ; 
 int /*<<< orphan*/  klv_encode_ber_length (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxf_write_essence_container_refs (TYPE_3__*) ; 
 int /*<<< orphan*/  mxf_write_local_tag (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxf_write_refs_count (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op1a_ul ; 
 int /*<<< orphan*/  opatom_ul ; 

__attribute__((used)) static void mxf_write_preface(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;

    mxf_write_metadata_key(pb, 0x012f00);
    PRINT_KEY(s, "preface key", pb->buf_ptr - 16);
    klv_encode_ber_length(pb, 138 + 16LL * DESCRIPTOR_COUNT(mxf->essence_container_count));

    // write preface set uid
    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, Preface, 0);
    PRINT_KEY(s, "preface uid", pb->buf_ptr - 16);

    // last modified date
    mxf_write_local_tag(pb, 8, 0x3B02);
    avio_wb64(pb, mxf->timestamp);

    // write version
    mxf_write_local_tag(pb, 2, 0x3B05);
    avio_wb16(pb, 259); // v1.3

    // Object Model Version
    mxf_write_local_tag(pb, 4, 0x3B07);
    avio_wb32(pb, 1);

    // write identification_refs
    mxf_write_local_tag(pb, 16 + 8, 0x3B06);
    mxf_write_refs_count(pb, 1);
    mxf_write_uuid(pb, Identification, 0);

    // write content_storage_refs
    mxf_write_local_tag(pb, 16, 0x3B03);
    mxf_write_uuid(pb, ContentStorage, 0);

    // operational pattern
    mxf_write_local_tag(pb, 16, 0x3B09);
    if (s->oformat == &ff_mxf_opatom_muxer)
        avio_write(pb, opatom_ul, 16);
    else
        avio_write(pb, op1a_ul, 16);

    // write essence_container_refs
    mxf_write_local_tag(pb, 8 + 16LL * DESCRIPTOR_COUNT(mxf->essence_container_count), 0x3B0A);
    mxf_write_essence_container_refs(s);

    // write dm_scheme_refs
    mxf_write_local_tag(pb, 8, 0x3B0B);
    avio_wb64(pb, 0);
}