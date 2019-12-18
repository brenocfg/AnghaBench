#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_14__ {TYPE_3__** asf_st; } ;
struct TYPE_10__ {unsigned char* data; } ;
struct TYPE_13__ {int data_size; TYPE_1__ avpkt; } ;
struct TYPE_12__ {int virtual_pkt_len; int virtual_chunk_len; int span; } ;
struct TYPE_11__ {TYPE_5__* priv_data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFStream ;
typedef  TYPE_4__ ASFPacket ;
typedef  TYPE_5__ ASFContext ;

/* Variables and functions */
 int av_new_packet (TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int asf_deinterleave(AVFormatContext *s, ASFPacket *asf_pkt, int st_num)
{
    ASFContext *asf    = s->priv_data;
    ASFStream *asf_st  = asf->asf_st[st_num];
    unsigned char *p   = asf_pkt->avpkt.data;
    uint16_t pkt_len   = asf->asf_st[st_num]->virtual_pkt_len;
    uint16_t chunk_len = asf->asf_st[st_num]->virtual_chunk_len;
    int nchunks        = pkt_len / chunk_len;
    AVPacket pkt;
    int pos = 0, j, l, ret;


    if ((ret = av_new_packet(&pkt, asf_pkt->data_size)) < 0)
        return ret;

    while (asf_pkt->data_size >= asf_st->span * pkt_len + pos) {
        if (pos >= asf_pkt->data_size) {
            break;
        }
        for (l = 0; l < pkt_len; l++) {
            if (pos >= asf_pkt->data_size) {
                break;
            }
            for (j = 0; j < asf_st->span; j++) {
                if ((pos + chunk_len) >= asf_pkt->data_size)
                    break;
                memcpy(pkt.data + pos,
                       p + (j * nchunks + l) * chunk_len,
                       chunk_len);
                pos += chunk_len;
            }
        }
        p += asf_st->span * pkt_len;
        if (p > asf_pkt->avpkt.data + asf_pkt->data_size)
            break;
    }
    av_packet_unref(&asf_pkt->avpkt);
    asf_pkt->avpkt = pkt;

    return 0;
}