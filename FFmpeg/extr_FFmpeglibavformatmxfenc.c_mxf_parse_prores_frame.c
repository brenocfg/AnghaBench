#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int profile; int /*<<< orphan*/  codec_ul; } ;
struct TYPE_17__ {TYPE_3__* priv_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  size; } ;
struct TYPE_15__ {TYPE_1__* codecpar; TYPE_2__* priv_data; } ;
struct TYPE_14__ {scalar_t__ header_written; } ;
struct TYPE_13__ {int /*<<< orphan*/  frame_size; int /*<<< orphan*/ * codec_ul; } ;
struct TYPE_12__ {int profile; } ;
typedef  TYPE_2__ MXFStreamContext ;
typedef  TYPE_3__ MXFContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_7__*) ; 
 TYPE_7__* mxf_prores_codec_uls ; 

__attribute__((used)) static int mxf_parse_prores_frame(AVFormatContext *s, AVStream *st, AVPacket *pkt)
{
    MXFContext *mxf = s->priv_data;
    MXFStreamContext *sc = st->priv_data;
    int i, profile;

    if (mxf->header_written)
        return 1;

    sc->codec_ul = NULL;
    profile = st->codecpar->profile;
    for (i = 0; i < FF_ARRAY_ELEMS(mxf_prores_codec_uls); i++) {
        if (profile == mxf_prores_codec_uls[i].profile) {
            sc->codec_ul = &mxf_prores_codec_uls[i].codec_ul;
            break;
        }
    }
    if (!sc->codec_ul)
        return 0;

    sc->frame_size = pkt->size;

    return 1;
}