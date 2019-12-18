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
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int* data; } ;
struct TYPE_6__ {int data_type; int pkt_offset; } ;
typedef  TYPE_1__ IEC61937Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AC3_FRAME_SIZE ; 
 int IEC61937_AC3 ; 

__attribute__((used)) static int spdif_header_ac3(AVFormatContext *s, AVPacket *pkt)
{
    IEC61937Context *ctx = s->priv_data;
    int bitstream_mode = pkt->data[5] & 0x7;

    ctx->data_type  = IEC61937_AC3 | (bitstream_mode << 8);
    ctx->pkt_offset = AC3_FRAME_SIZE << 2;
    return 0;
}