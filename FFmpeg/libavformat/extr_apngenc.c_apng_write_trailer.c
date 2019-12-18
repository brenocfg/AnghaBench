#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  plays; int /*<<< orphan*/  frame_number; scalar_t__ acTL_offset; scalar_t__ prev_packet; } ;
struct TYPE_9__ {TYPE_1__* pb; TYPE_3__* priv_data; } ;
struct TYPE_8__ {int seekable; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ APNGMuxContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  apng_write_chunk (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_seek (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int flush_packet (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apng_write_trailer(AVFormatContext *format_context)
{
    APNGMuxContext *apng = format_context->priv_data;
    AVIOContext *io_context = format_context->pb;
    uint8_t buf[8];
    int ret;

    if (apng->prev_packet) {
        ret = flush_packet(format_context, NULL);
        if (ret < 0)
            return ret;
    }

    apng_write_chunk(io_context, MKBETAG('I', 'E', 'N', 'D'), NULL, 0);

    if (apng->acTL_offset && (io_context->seekable & AVIO_SEEKABLE_NORMAL)) {
        avio_seek(io_context, apng->acTL_offset, SEEK_SET);

        AV_WB32(buf, apng->frame_number);
        AV_WB32(buf + 4, apng->plays);
        apng_write_chunk(io_context, MKBETAG('a', 'c', 'T', 'L'), buf, 8);
    }

    return 0;
}