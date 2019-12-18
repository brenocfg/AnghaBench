#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int pce_size; int /*<<< orphan*/ * pce_data; scalar_t__ write_adts; } ;
struct TYPE_16__ {int /*<<< orphan*/  extradata; int /*<<< orphan*/  extradata_size; } ;
struct TYPE_15__ {int /*<<< orphan*/ * pb; TYPE_1__** streams; TYPE_5__* priv_data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {TYPE_4__* codecpar; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;
typedef  TYPE_5__ ADTSContext ;

/* Variables and functions */
 int ADTS_HEADER_SIZE ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int adts_decode_extradata (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int adts_write_frame_header (TYPE_5__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ff_alloc_extradata (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adts_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    ADTSContext *adts = s->priv_data;
    AVCodecParameters *par = s->streams[0]->codecpar;
    AVIOContext *pb = s->pb;
    uint8_t buf[ADTS_HEADER_SIZE];

    if (!pkt->size)
        return 0;
    if (!par->extradata_size) {
        uint8_t *side_data;
        int side_data_size = 0, ret;

        side_data = av_packet_get_side_data(pkt, AV_PKT_DATA_NEW_EXTRADATA,
                                            &side_data_size);
        if (side_data_size) {
            ret = adts_decode_extradata(s, adts, side_data, side_data_size);
            if (ret < 0)
                return ret;
            ret = ff_alloc_extradata(par, side_data_size);
            if (ret < 0)
                return ret;
            memcpy(par->extradata, side_data, side_data_size);
        }
    }
    if (adts->write_adts) {
        int err = adts_write_frame_header(adts, buf, pkt->size,
                                             adts->pce_size);
        if (err < 0)
            return err;
        avio_write(pb, buf, ADTS_HEADER_SIZE);
        if (adts->pce_size) {
            avio_write(pb, adts->pce_data, adts->pce_size);
            adts->pce_size = 0;
        }
    }
    avio_write(pb, pkt->data, pkt->size);

    return 0;
}