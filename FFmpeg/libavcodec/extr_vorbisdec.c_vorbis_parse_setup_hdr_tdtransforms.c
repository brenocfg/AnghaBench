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
struct TYPE_3__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ vorbis_context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vorbis_parse_setup_hdr_tdtransforms(vorbis_context *vc)
{
    GetBitContext *gb = &vc->gb;
    unsigned i, vorbis_time_count = get_bits(gb, 6) + 1;

    for (i = 0; i < vorbis_time_count; ++i) {
        unsigned vorbis_tdtransform = get_bits(gb, 16);

        ff_dlog(NULL, " Vorbis time domain transform %u: %u\n",
                vorbis_time_count, vorbis_tdtransform);

        if (vorbis_tdtransform) {
            av_log(vc->avctx, AV_LOG_ERROR, "Vorbis time domain transform data nonzero. \n");
            return AVERROR_INVALIDDATA;
        }
    }
    return 0;
}