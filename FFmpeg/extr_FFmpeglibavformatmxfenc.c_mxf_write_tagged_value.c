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
struct TYPE_5__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tagged_value_count; } ;
typedef  TYPE_1__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  TaggedValue ; 
 int /*<<< orphan*/  avio_put_str16le (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  klv_encode_ber_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxf_indirect_value_utf16le ; 
 int mxf_utf16_local_tag_length (char const*) ; 
 int /*<<< orphan*/  mxf_write_local_tag (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mxf_write_local_tag_utf16 (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxf_write_tagged_value(AVFormatContext *s, const char* name, const char* value)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int name_size = mxf_utf16_local_tag_length(name);
    int indirect_value_size = 13 + mxf_utf16_local_tag_length(value);

    if (!name_size || indirect_value_size == 13)
        return 1;

    mxf_write_metadata_key(pb, 0x013f00);
    klv_encode_ber_length(pb, 24 + name_size + indirect_value_size);

    // write instance UID
    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, TaggedValue, mxf->tagged_value_count);

    // write name
    mxf_write_local_tag_utf16(pb, 0x5001, name); // Name

    // write indirect value
    mxf_write_local_tag(pb, indirect_value_size, 0x5003);
    avio_write(pb, mxf_indirect_value_utf16le, 17);
    avio_put_str16le(pb, value);

    mxf->tagged_value_count++;
    return 0;
}