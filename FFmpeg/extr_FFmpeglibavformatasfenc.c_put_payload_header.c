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
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ multi_payloads_present; int /*<<< orphan*/  pb; } ;
struct TYPE_7__ {int num; int seq; } ;
struct TYPE_6__ {TYPE_3__* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASFStream ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */
 int ASF_PAYLOAD_REPLICATED_DATA_LENGTH ; 
 int ASF_PL_FLAG_KEY_FRAME ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void put_payload_header(AVFormatContext *s, ASFStream *stream,
                               int64_t presentation_time, int m_obj_size,
                               int m_obj_offset, int payload_len, int flags)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = &asf->pb;
    int val;

    val = stream->num;
    if (flags & AV_PKT_FLAG_KEY)
        val |= ASF_PL_FLAG_KEY_FRAME;
    avio_w8(pb, val);

    avio_w8(pb, stream->seq);     // Media object number
    avio_wl32(pb, m_obj_offset);  // Offset Into Media Object

    // Replicated Data shall be at least 8 bytes long.
    // The first 4 bytes of data shall contain the
    // Size of the Media Object that the payload belongs to.
    // The next 4 bytes of data shall contain the
    // Presentation Time for the media object that the payload belongs to.
    avio_w8(pb, ASF_PAYLOAD_REPLICATED_DATA_LENGTH);

    avio_wl32(pb, m_obj_size);        // Replicated Data - Media Object Size
    avio_wl32(pb, (uint32_t) presentation_time); // Replicated Data - Presentation Time

    if (asf->multi_payloads_present) {
        avio_wl16(pb, payload_len);   // payload length
    }
}