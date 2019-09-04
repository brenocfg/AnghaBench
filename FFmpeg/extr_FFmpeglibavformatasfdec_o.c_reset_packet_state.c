#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; TYPE_1__** asf_st; scalar_t__ sub_dts; scalar_t__ prop_flags; scalar_t__ nb_sub; scalar_t__ nb_mult_left; scalar_t__ mult_sub_len; scalar_t__ dts_delta; scalar_t__ rep_data_len; scalar_t__ pad_len; int /*<<< orphan*/  first_packet_offset; int /*<<< orphan*/  packet_offset; scalar_t__ sub_header_offset; scalar_t__ sub_left; scalar_t__ return_subpayload; scalar_t__ offset; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {int /*<<< orphan*/  avpkt; scalar_t__ duration; scalar_t__ dts; scalar_t__ flags; scalar_t__ data_size; scalar_t__ size_left; } ;
struct TYPE_7__ {TYPE_4__* priv_data; } ;
struct TYPE_6__ {TYPE_3__ pkt; } ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFPacket ;
typedef  TYPE_4__ ASFContext ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_PACKET_HEADER ; 
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_packet_state(AVFormatContext *s)
{
    ASFContext *asf        = s->priv_data;
    int i;

    asf->state             = PARSE_PACKET_HEADER;
    asf->offset            = 0;
    asf->return_subpayload = 0;
    asf->sub_left          = 0;
    asf->sub_header_offset = 0;
    asf->packet_offset     = asf->first_packet_offset;
    asf->pad_len           = 0;
    asf->rep_data_len      = 0;
    asf->dts_delta         = 0;
    asf->mult_sub_len      = 0;
    asf->nb_mult_left      = 0;
    asf->nb_sub            = 0;
    asf->prop_flags        = 0;
    asf->sub_dts           = 0;
    for (i = 0; i < asf->nb_streams; i++) {
        ASFPacket *pkt = &asf->asf_st[i]->pkt;
        pkt->size_left = 0;
        pkt->data_size = 0;
        pkt->duration  = 0;
        pkt->flags     = 0;
        pkt->dts       = 0;
        pkt->duration  = 0;
        av_packet_unref(&pkt->avpkt);
        av_init_packet(&pkt->avpkt);
    }
}