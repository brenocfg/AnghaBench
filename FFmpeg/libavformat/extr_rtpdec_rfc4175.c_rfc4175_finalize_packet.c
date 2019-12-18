#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int stream_index; } ;
struct TYPE_6__ {int /*<<< orphan*/ * frame; int /*<<< orphan*/  frame_size; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int av_packet_from_data (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfc4175_finalize_packet(PayloadContext *data, AVPacket *pkt,
                                   int stream_index)
{
   int ret;

   pkt->stream_index = stream_index;
   ret = av_packet_from_data(pkt, data->frame, data->frame_size);
   if (ret < 0) {
       av_freep(&data->frame);
   }

   data->frame = NULL;

   return ret;
}