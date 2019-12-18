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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_7__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {int profile; int level; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVCSubDescriptor ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  klv_encode_ber4_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_avc_subdescriptor_key ; 
 int /*<<< orphan*/  mxf_update_klv_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_local_tag (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxf_write_avc_subdesc(AVFormatContext *s, AVStream *st)
{
    AVIOContext *pb = s->pb;
    int64_t pos;

    avio_write(pb, mxf_avc_subdescriptor_key, 16);
    klv_encode_ber4_length(pb, 0);
    pos = avio_tell(pb);

    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, AVCSubDescriptor, 0);

    mxf_write_local_tag(pb, 1, 0x8200);
    avio_w8(pb, 0xFF); // AVC Decoding Delay, unknown

    mxf_write_local_tag(pb, 1, 0x8201);
    avio_w8(pb, st->codecpar->profile); // AVC Profile

    mxf_write_local_tag(pb, 1, 0x8202);
    avio_w8(pb, st->codecpar->level); // AVC Level

    mxf_update_klv_size(s->pb, pos);
}