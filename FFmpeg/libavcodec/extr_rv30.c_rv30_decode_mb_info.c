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
struct TYPE_5__ {scalar_t__ pict_type; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
struct TYPE_4__ {TYPE_2__ s; } ;
typedef  TYPE_1__ RV34DecContext ;
typedef  TYPE_2__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
#define  RV34_MB_B_BACKWARD 135 
#define  RV34_MB_B_DIRECT 134 
#define  RV34_MB_B_FORWARD 133 
#define  RV34_MB_P_16x16 132 
#define  RV34_MB_P_8x8 131 
#define  RV34_MB_SKIP 130 
#define  RV34_MB_TYPE_INTRA 129 
#define  RV34_MB_TYPE_INTRA16x16 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 unsigned int get_interleaved_ue_golomb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rv30_decode_mb_info(RV34DecContext *r)
{
    static const int rv30_p_types[6] = { RV34_MB_SKIP, RV34_MB_P_16x16, RV34_MB_P_8x8, -1, RV34_MB_TYPE_INTRA, RV34_MB_TYPE_INTRA16x16 };
    static const int rv30_b_types[6] = { RV34_MB_SKIP, RV34_MB_B_DIRECT, RV34_MB_B_FORWARD, RV34_MB_B_BACKWARD, RV34_MB_TYPE_INTRA, RV34_MB_TYPE_INTRA16x16 };
    MpegEncContext *s = &r->s;
    GetBitContext *gb = &s->gb;
    unsigned code = get_interleaved_ue_golomb(gb);

    if (code > 11) {
        av_log(s->avctx, AV_LOG_ERROR, "Incorrect MB type code\n");
        return -1;
    }
    if(code > 5){
        av_log(s->avctx, AV_LOG_ERROR, "dquant needed\n");
        code -= 6;
    }
    if(s->pict_type != AV_PICTURE_TYPE_B)
        return rv30_p_types[code];
    else
        return rv30_b_types[code];
}