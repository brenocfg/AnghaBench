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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_2__* sys; TYPE_1__* avctx; } ;
struct TYPE_7__ {int height; int n_difchan; int difseg_size; scalar_t__ dsf; } ;
struct TYPE_6__ {int frame_number; } ;
typedef  TYPE_3__ DVVideoContext ;

/* Variables and functions */
 int /*<<< orphan*/  dv_header525 ; 
 int /*<<< orphan*/  dv_header625 ; 
 int /*<<< orphan*/  dv_sect_audio ; 
 int /*<<< orphan*/  dv_sect_header ; 
 int /*<<< orphan*/  dv_sect_subcode ; 
 int /*<<< orphan*/  dv_sect_vaux ; 
 int /*<<< orphan*/  dv_sect_video ; 
 int /*<<< orphan*/  dv_video_control ; 
 int /*<<< orphan*/  dv_video_source ; 
 int /*<<< orphan*/  dv_write_dif_id (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dv_write_pack (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dv_write_ssyb_id (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void dv_format_frame(DVVideoContext *c, uint8_t *buf)
{
    int chan, i, j, k;
    /* We work with 720p frames split in half. The odd half-frame is chan 2,3 */
    int chan_offset = 2*(c->sys->height == 720 && c->avctx->frame_number & 1);

    for (chan = 0; chan < c->sys->n_difchan; chan++) {
        for (i = 0; i < c->sys->difseg_size; i++) {
            memset(buf, 0xff, 80 * 6); /* first 6 DIF blocks are for control data */

            /* DV header: 1DIF */
            buf += dv_write_dif_id(dv_sect_header, chan+chan_offset, i, 0, buf);
            buf += dv_write_pack((c->sys->dsf ? dv_header625 : dv_header525),
                                 c, buf);
            buf += 72; /* unused bytes */

            /* DV subcode: 2DIFs */
            for (j = 0; j < 2; j++) {
                buf += dv_write_dif_id(dv_sect_subcode, chan+chan_offset, i, j, buf);
                for (k = 0; k < 6; k++)
                    buf += dv_write_ssyb_id(k, (i < c->sys->difseg_size / 2), buf) + 5;
                buf += 29; /* unused bytes */
            }

            /* DV VAUX: 3DIFS */
            for (j = 0; j < 3; j++) {
                buf += dv_write_dif_id(dv_sect_vaux, chan+chan_offset, i, j, buf);
                buf += dv_write_pack(dv_video_source,  c, buf);
                buf += dv_write_pack(dv_video_control, c, buf);
                buf += 7 * 5;
                buf += dv_write_pack(dv_video_source,  c, buf);
                buf += dv_write_pack(dv_video_control, c, buf);
                buf += 4 * 5 + 2; /* unused bytes */
            }

            /* DV Audio/Video: 135 Video DIFs + 9 Audio DIFs */
            for (j = 0; j < 135; j++) {
                if (j % 15 == 0) {
                    memset(buf, 0xff, 80);
                    buf += dv_write_dif_id(dv_sect_audio, chan+chan_offset, i, j/15, buf);
                    buf += 77; /* audio control & shuffled PCM audio */
                }
                buf += dv_write_dif_id(dv_sect_video, chan+chan_offset, i, j, buf);
                buf += 77; /* 1 video macroblock: 1 bytes control
                            * 4 * 14 bytes Y 8x8 data
                            * 10 bytes Cr 8x8 data
                            * 10 bytes Cb 8x8 data */
            }
        }
    }
}