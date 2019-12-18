#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {size_t last_stsd_index; size_t stsc_index; int* extradata_size; int /*<<< orphan*/ ** extradata; TYPE_1__* stsc_data; } ;
struct TYPE_4__ {size_t id; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_packet_new_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mov_change_extradata(MOVStreamContext *sc, AVPacket *pkt)
{
    uint8_t *side, *extradata;
    int extradata_size;

    /* Save the current index. */
    sc->last_stsd_index = sc->stsc_data[sc->stsc_index].id - 1;

    /* Notify the decoder that extradata changed. */
    extradata_size = sc->extradata_size[sc->last_stsd_index];
    extradata = sc->extradata[sc->last_stsd_index];
    if (extradata_size > 0 && extradata) {
        side = av_packet_new_side_data(pkt,
                                       AV_PKT_DATA_NEW_EXTRADATA,
                                       extradata_size);
        if (!side)
            return AVERROR(ENOMEM);
        memcpy(side, extradata, extradata_size);
    }

    return 0;
}