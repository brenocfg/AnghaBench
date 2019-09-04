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
struct TYPE_9__ {int nb_streams; TYPE_3__** streams; int /*<<< orphan*/ * oformat; TYPE_2__* priv_data; } ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ edit_unit_byte_count; } ;
struct TYPE_6__ {scalar_t__ frame_size; scalar_t__ slice_offset; } ;
typedef  TYPE_1__ MXFStreamContext ;
typedef  TYPE_2__ MXFContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ KAG_SIZE ; 
 int /*<<< orphan*/  ff_mxf_opatom_muxer ; 
 scalar_t__ klv_fill_size (scalar_t__) ; 

__attribute__((used)) static void mxf_compute_edit_unit_byte_count(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    int i;

    if (s->oformat == &ff_mxf_opatom_muxer) {
        MXFStreamContext *sc = s->streams[0]->priv_data;
        mxf->edit_unit_byte_count = sc->frame_size;
        return;
    }

    mxf->edit_unit_byte_count = KAG_SIZE; // system element
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        MXFStreamContext *sc = st->priv_data;
        sc->slice_offset = mxf->edit_unit_byte_count;
        mxf->edit_unit_byte_count += 16 + 4 + sc->frame_size;
        mxf->edit_unit_byte_count += klv_fill_size(mxf->edit_unit_byte_count);
    }
}