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
typedef  int int8_t ;
struct TYPE_4__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {int intra_types_stride; TYPE_1__ s; } ;
typedef  TYPE_2__ RV34DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int get_interleaved_ue_golomb (int /*<<< orphan*/ *) ; 
 int* rv30_itype_code ; 
 int /*<<< orphan*/ * rv30_itype_from_context ; 

__attribute__((used)) static int rv30_decode_intra_types(RV34DecContext *r, GetBitContext *gb, int8_t *dst)
{
    int i, j, k;

    for(i = 0; i < 4; i++, dst += r->intra_types_stride - 4){
        for(j = 0; j < 4; j+= 2){
            unsigned code = get_interleaved_ue_golomb(gb) << 1;
            if (code > 80U*2U) {
                av_log(r->s.avctx, AV_LOG_ERROR, "Incorrect intra prediction code\n");
                return -1;
            }
            for(k = 0; k < 2; k++){
                int A = dst[-r->intra_types_stride] + 1;
                int B = dst[-1] + 1;
                *dst++ = rv30_itype_from_context[A * 90 + B * 9 + rv30_itype_code[code + k]];
                if(dst[-1] == 9){
                    av_log(r->s.avctx, AV_LOG_ERROR, "Incorrect intra prediction mode\n");
                    return -1;
                }
            }
        }
    }
    return 0;
}