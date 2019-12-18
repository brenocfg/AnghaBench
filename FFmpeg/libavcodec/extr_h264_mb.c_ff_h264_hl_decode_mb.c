#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int* mb_type; } ;
struct TYPE_19__ {scalar_t__ pixel_shift; TYPE_1__ cur_pic; } ;
struct TYPE_18__ {int mb_xy; scalar_t__ qscale; int /*<<< orphan*/  is_complex; } ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H264Context ;

/* Variables and functions */
 scalar_t__ CHROMA444 (TYPE_3__ const*) ; 
 scalar_t__ CONFIG_SMALL ; 
 scalar_t__ IS_INTRA_PCM (int const) ; 
 int /*<<< orphan*/  hl_decode_mb_444_complex (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  hl_decode_mb_444_simple_8 (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  hl_decode_mb_complex (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  hl_decode_mb_simple_16 (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  hl_decode_mb_simple_8 (TYPE_3__ const*,TYPE_2__*) ; 

void ff_h264_hl_decode_mb(const H264Context *h, H264SliceContext *sl)
{
    const int mb_xy   = sl->mb_xy;
    const int mb_type = h->cur_pic.mb_type[mb_xy];
    int is_complex    = CONFIG_SMALL || sl->is_complex ||
                        IS_INTRA_PCM(mb_type) || sl->qscale == 0;

    if (CHROMA444(h)) {
        if (is_complex || h->pixel_shift)
            hl_decode_mb_444_complex(h, sl);
        else
            hl_decode_mb_444_simple_8(h, sl);
    } else if (is_complex) {
        hl_decode_mb_complex(h, sl);
    } else if (h->pixel_shift) {
        hl_decode_mb_simple_16(h, sl);
    } else
        hl_decode_mb_simple_8(h, sl);
}