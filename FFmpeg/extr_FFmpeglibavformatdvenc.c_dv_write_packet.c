#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct AVFormatContext {int /*<<< orphan*/  pb; int /*<<< orphan*/ * streams; int /*<<< orphan*/  priv_data; } ;
struct TYPE_3__ {size_t stream_index; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int dv_assemble_frame (struct AVFormatContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int dv_write_packet(struct AVFormatContext *s, AVPacket *pkt)
{
    uint8_t* frame;
    int fsize;

    fsize = dv_assemble_frame(s, s->priv_data, s->streams[pkt->stream_index],
                              pkt->data, pkt->size, &frame);
    if (fsize > 0) {
        avio_write(s->pb, frame, fsize);
    }
    return 0;
}