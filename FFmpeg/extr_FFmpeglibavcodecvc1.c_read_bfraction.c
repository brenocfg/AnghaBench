#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {int bfraction_lut_index; int /*<<< orphan*/  bfraction; TYPE_1__ s; } ;
typedef  TYPE_2__ VC1Context ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  VC1_BFRACTION_VLC_BITS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ff_vc1_bfraction_lut ; 
 TYPE_4__ ff_vc1_bfraction_vlc ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_bfraction(VC1Context *v, GetBitContext* gb) {
    int bfraction_lut_index = get_vlc2(gb, ff_vc1_bfraction_vlc.table, VC1_BFRACTION_VLC_BITS, 1);

    if (bfraction_lut_index == 21 || bfraction_lut_index < 0) {
        av_log(v->s.avctx, AV_LOG_ERROR, "bfraction invalid\n");
        return AVERROR_INVALIDDATA;
    }
    v->bfraction_lut_index = bfraction_lut_index;
    v->bfraction           = ff_vc1_bfraction_lut[v->bfraction_lut_index];
    return 0;
}