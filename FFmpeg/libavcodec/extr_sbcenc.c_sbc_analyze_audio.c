#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sbc_frame {int subbands; int channels; int blocks; scalar_t__** sb_sample_f; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int increment; int /*<<< orphan*/  (* sbc_analyze_8s ) (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ;int /*<<< orphan*/  position; int /*<<< orphan*/ ** X; int /*<<< orphan*/  (* sbc_analyze_4s ) (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ;} ;
typedef  TYPE_1__ SBCDSPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sbc_analyze_audio(SBCDSPContext *s, struct sbc_frame *frame)
{
    int ch, blk;
    int16_t *x;

    switch (frame->subbands) {
    case 4:
        for (ch = 0; ch < frame->channels; ch++) {
            x = &s->X[ch][s->position - 4 *
                    s->increment + frame->blocks * 4];
            for (blk = 0; blk < frame->blocks;
                        blk += s->increment) {
                s->sbc_analyze_4s(
                    s, x,
                    frame->sb_sample_f[blk][ch],
                    frame->sb_sample_f[blk + 1][ch] -
                    frame->sb_sample_f[blk][ch]);
                x -= 4 * s->increment;
            }
        }
        return frame->blocks * 4;

    case 8:
        for (ch = 0; ch < frame->channels; ch++) {
            x = &s->X[ch][s->position - 8 *
                    s->increment + frame->blocks * 8];
            for (blk = 0; blk < frame->blocks;
                        blk += s->increment) {
                s->sbc_analyze_8s(
                    s, x,
                    frame->sb_sample_f[blk][ch],
                    frame->sb_sample_f[blk + 1][ch] -
                    frame->sb_sample_f[blk][ch]);
                x -= 8 * s->increment;
            }
        }
        return frame->blocks * 8;

    default:
        return AVERROR(EIO);
    }
}