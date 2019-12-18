#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  EssenceContainerData ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  klv_encode_ber_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxf_write_local_tag (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxf_write_umid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxf_write_essence_container_data(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;

    mxf_write_metadata_key(pb, 0x012300);
    klv_encode_ber_length(pb, 72);

    mxf_write_local_tag(pb, 16, 0x3C0A); // Instance UID
    mxf_write_uuid(pb, EssenceContainerData, 0);

    mxf_write_local_tag(pb, 32, 0x2701); // Linked Package UID
    mxf_write_umid(s, 1);

    mxf_write_local_tag(pb, 4, 0x3F07); // BodySID
    avio_wb32(pb, 1);

    mxf_write_local_tag(pb, 4, 0x3F06); // IndexSID
    avio_wb32(pb, 2);

    return 0;
}