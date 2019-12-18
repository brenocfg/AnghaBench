#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int flags; int /*<<< orphan*/ * oformat; TYPE_2__* pb; TYPE_1__* priv_data; } ;
struct TYPE_14__ {scalar_t__ buf_ptr; } ;
struct TYPE_13__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ MXFContext ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVFMT_FLAG_BITEXACT ; 
 char* AV_STRINGIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Identification ; 
 int /*<<< orphan*/  LIBAVFORMAT_VERSION ; 
 int /*<<< orphan*/  PRINT_KEY (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  avio_wb64 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mxf_opatom_muxer ; 
 int /*<<< orphan*/  klv_encode_ber_length (TYPE_2__*,int) ; 
 int mxf_utf16_local_tag_length (char const*) ; 
 int /*<<< orphan*/  mxf_write_local_tag (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  mxf_write_local_tag_utf16 (TYPE_2__*,int,char const*) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_version (TYPE_3__*) ; 

__attribute__((used)) static void mxf_write_identification(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    const char *company = "FFmpeg";
    const char *product = s->oformat != &ff_mxf_opatom_muxer ? "OP1a Muxer" : "OPAtom Muxer";
    const char *version;
    int length;

    mxf_write_metadata_key(pb, 0x013000);
    PRINT_KEY(s, "identification key", pb->buf_ptr - 16);

    version = s->flags & AVFMT_FLAG_BITEXACT ?
        "0.0.0" : AV_STRINGIFY(LIBAVFORMAT_VERSION);
    length = 100 +mxf_utf16_local_tag_length(company) +
                  mxf_utf16_local_tag_length(product) +
                  mxf_utf16_local_tag_length(version);
    klv_encode_ber_length(pb, length);

    // write uid
    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, Identification, 0);
    PRINT_KEY(s, "identification uid", pb->buf_ptr - 16);

    // write generation uid
    mxf_write_local_tag(pb, 16, 0x3C09);
    mxf_write_uuid(pb, Identification, 1);
    mxf_write_local_tag_utf16(pb, 0x3C01, company); // Company Name
    mxf_write_local_tag_utf16(pb, 0x3C02, product); // Product Name

    mxf_write_local_tag(pb, 10, 0x3C03); // Product Version
    store_version(s);

    mxf_write_local_tag_utf16(pb, 0x3C04, version); // Version String

    // write product uid
    mxf_write_local_tag(pb, 16, 0x3C05);
    mxf_write_uuid(pb, Identification, 2);

    // modification date
    mxf_write_local_tag(pb, 8, 0x3C06);
    avio_wb64(pb, mxf->timestamp);

    mxf_write_local_tag(pb, 10, 0x3C07); // Toolkit Version
    store_version(s);
}