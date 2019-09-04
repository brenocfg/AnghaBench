#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int media_type; int sample_rate; char media_info; int track_type; int sample_size; int /*<<< orphan*/  fields; int /*<<< orphan*/  lines_index; int /*<<< orphan*/  frame_rate_index; } ;
typedef  TYPE_1__ GXFStreamContext ;

/* Variables and functions */

__attribute__((used)) static void gxf_init_timecode_track(GXFStreamContext *sc, GXFStreamContext *vsc)
{
    if (!vsc)
        return;

    sc->media_type = vsc->sample_rate == 60 ? 7 : 8;
    sc->sample_rate = vsc->sample_rate;
    sc->media_info = ('T'<<8) | '0';
    sc->track_type = 3;
    sc->frame_rate_index = vsc->frame_rate_index;
    sc->lines_index = vsc->lines_index;
    sc->sample_size = 16;
    sc->fields = vsc->fields;
}