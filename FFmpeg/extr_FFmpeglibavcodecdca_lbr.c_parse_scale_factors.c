#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ensure_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_dca_vlc_fst_rsd_amp ; 
 int /*<<< orphan*/  ff_dca_vlc_rsd_amp ; 
 int /*<<< orphan*/  ff_dca_vlc_rsd_apprx ; 
 int parse_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_scale_factors(DCALbrDecoder *s, uint8_t *scf)
{
    int i, sf, prev, next, dist;

    // Truncated scale factors remain zero
    if (ensure_bits(&s->gb, 20))
        return 0;

    // Initial scale factor
    prev = parse_vlc(&s->gb, &ff_dca_vlc_fst_rsd_amp, 2);

    for (sf = 0; sf < 7; sf += dist) {
        scf[sf] = prev; // Store previous value

        if (ensure_bits(&s->gb, 20))
            return 0;

        // Interpolation distance
        dist = parse_vlc(&s->gb, &ff_dca_vlc_rsd_apprx, 1) + 1;
        if (dist > 7 - sf) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid scale factor distance\n");
            return -1;
        }

        if (ensure_bits(&s->gb, 20))
            return 0;

        // Final interpolation point
        next = parse_vlc(&s->gb, &ff_dca_vlc_rsd_amp, 2);

        if (next & 1)
            next = prev + ((next + 1) >> 1);
        else
            next = prev - ( next      >> 1);

        // Interpolate
        switch (dist) {
        case 2:
            if (next > prev)
                scf[sf + 1] = prev + ((next - prev) >> 1);
            else
                scf[sf + 1] = prev - ((prev - next) >> 1);
            break;

        case 4:
            if (next > prev) {
                scf[sf + 1] = prev + ( (next - prev)      >> 2);
                scf[sf + 2] = prev + ( (next - prev)      >> 1);
                scf[sf + 3] = prev + (((next - prev) * 3) >> 2);
            } else {
                scf[sf + 1] = prev - ( (prev - next)      >> 2);
                scf[sf + 2] = prev - ( (prev - next)      >> 1);
                scf[sf + 3] = prev - (((prev - next) * 3) >> 2);
            }
            break;

        default:
            for (i = 1; i < dist; i++)
                scf[sf + i] = prev + (next - prev) * i / dist;
            break;
        }

        prev = next;
    }

    scf[sf] = next; // Store final value

    return 0;
}